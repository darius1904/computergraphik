#include <algorithm>
#include <cmath>
#include <limits>
#include <memory>
#include <tuple>
#include <vector>

#include "pointlight.h"
#include "scene.h"
#include "sceneobject.h"
#include "util.h"
#include "vec3.h"

const static int SEED = 42;

const static int WIDTH = 600;
const static int HEIGHT = 600;
const static int MAX_DEPTH = 5;

//////////
// TODO 2:
// Compute Phong lighting
//
Vec3d computePhongLighting(
    Vec3d const& view_direction,
    Vec3d const& surface_normal,
    Vec3d const& light_direction,
    PhongCoefficients const& phong_coeff,
    Vec3d const& light_color,
    double light_intensity)
{
    Vec3d n = surface_normal; n.normalize();
    Vec3d v = view_direction; v.normalize();
    Vec3d l = light_direction; l.normalize();

    Vec3d I_ambient = phong_coeff.k_a * light_intensity;
    double diff = std::max(0.0, n.dot(l));
    Vec3d I_diffuse = phong_coeff.k_d * diff * light_intensity;
    Vec3d r = (-l).reflect(n);
    double spec_angle = std::max(0.0, r.dot(v));
    double spec = pow(spec_angle, phong_coeff.n);
    Vec3d I_specular = light_color * phong_coeff.k_s * spec * light_intensity;

    return I_ambient + I_diffuse + I_specular;
}

/**
 * @brief Method to check a ray for intersections with any object of the scene.
 * @param ray The ray to trace.
 * @param objects Vector of pointers to all scene objects.
 * @param t_near The intersection distance from the ray origin to the closest point hit.
 * @param hitObject The closest object hit.
 * @return true on hit, false otherwise
 */
bool trace(const Ray& ray,
    const std::vector<std::shared_ptr<SceneObject>>& objects,
    double& t_near, std::shared_ptr<SceneObject>& hitObject)
{
    t_near = std::numeric_limits<double>::max();

    // Check all objects if they got hit by the traced ray.
    // If any object got hit, return the one closest to the camera as 'hitObject'.
    for (auto& o : objects)
    {
        double t = std::numeric_limits<double>::max();

        if (o->intersect(ray, t) && t < t_near)
        {
            hitObject = o;
            t_near = t;
        }
    }

    return (hitObject != nullptr);
}

/**
 * @brief Cast a ray into the scene. If the ray hits at least one object,
 *        the color of the object closest to the camera is returned.
 * @param ray The ray that's being cast.
 * @param objects All scene objects.
 * @return The color of a hit object that is closest to the camera.
 *         Return dark blue if no object was hit.
 */
Vec3d castRay(const Ray& ray, const std::vector<std::shared_ptr<SceneObject>>& objects,
    const std::vector<Pointlight>& lights)
{
    // set the background color as dark blue
    Vec3d hitColor(0, 0, 0.2);

    // early exit if maximum recursive depth is reached - return background color
    if (ray.depth > MAX_DEPTH)
        return hitColor;

    // pointer to the object that was hit by the ray
    std::shared_ptr<SceneObject> hitObject = nullptr;

    // intersection distance from the ray origin to the point hit
    double t = std::numeric_limits<double>::max();

    // Trace the ray. If an object gets hit, calculate the hit point and
    // retrieve the surface color 'hitColor' from the 'hitObject' object that was hit
    if (trace(ray, objects, t, hitObject))
    {
        hitColor = Vec3d();

        // Intersection point with the hit object
        const Vec3d p_hit = ray.origin + ray.dir * t;

        //////////
        // TODO 3:
        // Compute local lighting. The result is added to "hitColor".
        //
        // For each light source (given by funtion parameter lights)
        //
        //   a) Cast a shadow ray from the hitpoint to the light-source (use the trace function)
        //
        //   b) If not in shadow, compute local lighting using the function "computePhongLighting"
        //      Else apply ambient term only
        //
        //      For a more realistic image, use inverse square attentuation for the light intensity.
        //
        
        for (const auto& light : lights)
        {
            Vec3d lightDir = light._position - p_hit;
            double distToLight = lightDir.length();
            lightDir = lightDir; lightDir.normalize();

            Ray shadowRay;
            shadowRay.origin = p_hit + surface_normal * 1e-4;
            shadowRay.dir = lightDir;

            double t_shadow;
            std::shared_ptr<SceneObject> shadowHit = nullptr;

            bool inShadow = trace(shadowRay, objects, t_shadow, shadowHit)
                            && t_shadow < distToLight;

            double intensity = light._intensity / (distToLight * distToLight);

            if (!inShadow)
            {
                hitColor += computePhongLighting(
                    (ray.origin - p_hit).normalize(),
                    surface_normal,
                    lightDir,
                    phong,
                    light._color,
                    intensity
                );
            }
            else
            {
                hitColor += std::get<0>(phong) * intensity; // ambient
            }
        }

        // END TODO 3
        /////////////

        //////////
        // TODO 4:
        // Compute reflection.
        //
        // Build a reflection for the hitpoint of the hit object. 
        // Use this ray to make a recursive call to "castRay" and add the result of the call to "hitColor".
        //
        
        if (std::get<2>(phong).length() > 0.0) // k_s > 0
        {
            Vec3d v = (ray.origin - p_hit).normalize();
            Vec3d r = (-v).reflect(surface_normal).normalize();

            Ray reflectionRay;
            reflectionRay.origin = p_hit + surface_normal * 1e-4;
            reflectionRay.dir = r;
            reflectionRay.depth = ray.depth + 1;

            hitColor += 0.5 * castRay(reflectionRay, objects, lights);
        }


        // END TODO 4
        /////////////
    }

    return hitColor;
}

/**
 * @brief The rendering method, loop over all pixels in the framebuffer, shooting
 *        a ray through each pixel with the origing being the camera position.
 * @param viewport Size of the framebuffer.
 * @param objects Vector of pointers to all objects contained in the scene.
 */
void render(const Vec3i viewport, const std::vector<std::shared_ptr<SceneObject>>& objects,
    const std::vector<Pointlight>& lights)
{
    std::vector<Vec3d> framebuffer(static_cast<size_t>(viewport[0]) * viewport[1]);

    // camera position in world coordinates
    const Vec3d cameraPos(0., 0., 0.);

    // view plane parameters
    const double l = -1.;   // left
    const double r = +1.;   // right
    const double b = -1.;   // bottom
    const double t = +1.;   // top
    const double d = +2.;   // distance to camera

    // Cast a ray from 'cameraPos' through the center(!) of each pixel on the viewplane.
    // Use the view plane parametrization given above (l,r,b,t,d).
    #pragma omp parallel for
    for (int j = 0; j < viewport[1]; ++j)
    {
        for (int i = 0; i < viewport[0]; ++i)
        {
            double u = l + (r - l) * (i + 0.5) / viewport[0];
            double v = t + (b - t) * (j + 0.5) / viewport[1];

            Ray ray;
            ray.origin = cameraPos;
            ray.dir = Vec3d(u, v, -d) - cameraPos;
            ray.dir = ray.dir.normalize();
            framebuffer.at(i + j * static_cast<size_t>(viewport[0])) = castRay(ray, objects, lights);
        }
    }

    // save the framebuffer an a PPM image
    saveAsPPM("./result.ppm", viewport, framebuffer);
}

/**
 * @brief main routine.
 *        Generates the scene and invokes the rendering.
 * @return
 */
int main()
{
    // Generate the scene objects
    const auto objects = create_scene_objects();

    // Let there be light
    const auto lights = create_scene_lights();

    // Start rendering
    const Vec3i viewport(WIDTH, HEIGHT, 0);
    render(viewport, objects, lights);

    return 0;
}
