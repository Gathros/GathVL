#ifndef CAMERA_H
#define CAMERA_H

#include <memory>
#include <string>
#include <vector>

#include <cairo.h>

#include "encoder.h"
#include "png_encoder.h"
#include "video_encoder.h"
#include "vec.h"

struct scene;

struct camera {
    vec size;

    void clear_camera();

    void move_by(vec displace);
    void move_to(vec position);

    template <typename A, typename... Arg>
    void add_encoder(Arg&&... args) {
        encoders.emplace_back(std::make_unique<A>(std::forward<Arg>(args)...));
    }

    void encode_frame(scene &s);
    void clear_encoders();

    camera() : camera({0, 0}, {600, 400}) {}
    camera(vec camera_size) : camera({0, 0}, camera_size) {}
    camera(vec loc, vec camera_size);

private:
    vec location;
    std::vector<std::unique_ptr<encoder>> encoders;
    std::unique_ptr<cairo_surface_t, decltype(&cairo_surface_destroy)> image;
    std::unique_ptr<cairo_t, decltype(&cairo_destroy)> context;

    void capture(scene &s);
};

#endif //CAMERA_H
