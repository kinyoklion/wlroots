/*
 * This an unstable interface of wlroots. No guarantees are made regarding the
 * future consistency of this API.
 */
#ifndef WLR_USE_UNSTABLE
#error "Add -DWLR_USE_UNSTABLE to enable unstable API usage"
#endif

#ifndef WLR_UTIL_SERVER_SCALE_H
#define WLR_UTIL_SERVER_SCALE_H

#include <wayland-server-core.h>

/**
 * Register a client whose surfaces get a server-side scale override, the
 * mechanism behind "X11 clients apply scaling themselves": committed buffers
 * are displayed at 1/scale of their nominal size (treated as scale times
 * denser), and coordinates exchanged with the client (surface-local input,
 * xdg-output logical geometry) are multiplied by scale.
 *
 * Intended for the compositor's Xwayland connection. Only a single client at
 * a time is supported; pass NULL to clear the registration. The registration
 * is cleared automatically when the client is destroyed.
 */
void wlr_server_scale_set(struct wl_client *client, double scale);

/**
 * Get the scale override for a client. Returns 1.0 for unregistered clients
 * and NULL.
 */
double wlr_server_scale_get(const struct wl_client *client);

#endif
