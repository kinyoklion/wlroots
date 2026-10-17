# Fork notice

This repository is a fork of
[wlroots](https://gitlab.freedesktop.org/wlroots/wlroots). The default branch,
`master`, has the upstream code and one additional feature: a scale override
for Xwayland clients. The sway and SwayFX forks below use this feature.

## Purpose of the fork

Wayland compositors usually show X11 windows at scale 1. On a HiDPI output, the
compositor then makes the windows larger. The image is not clear.

This feature permits the compositor to set a scale for the Xwayland client. The
client then draws at the full resolution of the output. The compositor shows
the buffer at the logical size, and the image is clear.

The feature changes these parts of wlroots:

- `util/server_scale.c` adds `wlr_server_scale_set()` and
  `wlr_server_scale_get()`. They set and get the scale for one client.
- `types/scene/surface.c` divides the buffer size by the scale. It multiplies
  the input coordinates by the scale. It does not send fractional-scale events
  to the client.
- `types/wlr_xdg_output_v1.c` multiplies the logical output geometry by the
  scale for the client. `wlr_xdg_output_manager_v1_resend()` sends the new
  geometry after a scale change.

## Branches

- `master` is the default branch. It has upstream wlroots and the feature.
  [kinyoklion/sway](https://github.com/kinyoklion/sway) uses this branch.
- `x11-scaling-0.20` has wlroots 0.20.0 and the feature.
  [kinyoklion/swayfx](https://github.com/kinyoklion/swayfx) uses this branch.
- `x11-scaling` has the feature on the upstream commit of the first tests. Use
  `master` for new work.

## Related repositories

- [kinyoklion/sway](https://github.com/kinyoklion/sway): sway with the
  configuration commands for this feature.
- [kinyoklion/swayfx](https://github.com/kinyoklion/swayfx): SwayFX with the
  same configuration commands.

Each of these repositories also has the feature as a patch file in
`contrib/x11-scaling/wlroots/`.

The text that follows is the upstream README.

---

# wlroots

Pluggable, composable, unopinionated modules for building a [Wayland]
compositor; or about 60,000 lines of code you were going to write anyway.

- wlroots provides backends that abstract the underlying display and input
  hardware, including KMS/DRM, libinput, Wayland, X11, and headless backends,
  plus any custom backends you choose to write, which can all be created or
  destroyed at runtime and used in concert with each other.
- wlroots provides unopinionated, mostly standalone implementations of many
  Wayland interfaces, both from wayland.xml and various protocol extensions.
  We also promote the standardization of portable extensions across
  many compositors.
- wlroots provides several powerful, standalone, and optional tools that
  implement components common to many compositors, such as the arrangement of
  outputs in physical space.
- wlroots provides an Xwayland abstraction that allows you to have excellent
  Xwayland support without worrying about writing your own X11 window manager
  on top of writing your compositor.
- wlroots provides a renderer abstraction that simple compositors can use to
  avoid writing GL code directly, but which steps out of the way when your
  needs demand custom rendering code.

wlroots implements a huge variety of Wayland compositor features and implements
them *right*, so you can focus on the features that make your compositor
unique. By using wlroots, you get high performance, excellent hardware
compatibility, broad support for many wayland interfaces, and comfortable
development tools - or any subset of these features you like, because all of
them work independently of one another and freely compose with anything you want
to implement yourself.

Check out our [wiki] to get started with wlroots. Join our IRC channel:
[#wlroots on Libera Chat].

A variety of [wrapper libraries] are available for using it with your favorite
programming language.

## Building

Install dependencies:

* meson
* wayland
* wayland-protocols
* EGL and GLESv2 (optional, for the GLES2 renderer)
* Vulkan loader, headers and glslang (optional, for the Vulkan renderer)
* libdrm
* GBM (optional, for the GBM allocator)
* libinput (optional, for the libinput backend)
* xkbcommon
* udev (optional, for the session)
* pixman
* [libseat] (optional, for the session)
* [hwdata] (optional, for the DRM backend)
* [libdisplay-info] (optional, for the DRM backend)
* [libliftoff] (optional, for the DRM backend)

If you choose to enable X11 support:

* xwayland (build-time only, optional at runtime)
* libxcb
* libxcb-render-util
* libxcb-wm
* libxcb-errors (optional, for improved error reporting)

Run these commands:

    meson setup build/
    ninja -C build/

Install like so:

    sudo ninja -C build/ install

## Contributing

See [CONTRIBUTING.md].

[Wayland]: https://wayland.freedesktop.org/
[wiki]: https://gitlab.freedesktop.org/wlroots/wlroots/-/wikis/Getting-started
[#wlroots on Libera Chat]: https://web.libera.chat/gamja/?channels=#wlroots
[wrapper libraries]: https://gitlab.freedesktop.org/wlroots/wlroots/-/wikis/Projects-which-use-wlroots#wrapper-libraries
[libseat]: https://git.sr.ht/~kennylevinsen/seatd
[hwdata]: https://github.com/vcrhonek/hwdata
[libdisplay-info]: https://gitlab.freedesktop.org/emersion/libdisplay-info
[libliftoff]: https://gitlab.freedesktop.org/emersion/libliftoff
[CONTRIBUTING.md]: https://gitlab.freedesktop.org/wlroots/wlroots/-/blob/master/CONTRIBUTING.md
