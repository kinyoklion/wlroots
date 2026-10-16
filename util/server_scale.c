#include <assert.h>
#include <wayland-server-core.h>
#include <wlr/util/server_scale.h>

static struct wl_client *scaled_client = NULL;
static double scaled_client_scale = 1.0;
static struct wl_listener scaled_client_destroy;

static void handle_scaled_client_destroy(struct wl_listener *listener, void *data) {
	wl_list_remove(&scaled_client_destroy.link);
	scaled_client = NULL;
	scaled_client_scale = 1.0;
}

void wlr_server_scale_set(struct wl_client *client, double scale) {
	assert(scale > 0);
	if (scaled_client != NULL) {
		wl_list_remove(&scaled_client_destroy.link);
		scaled_client = NULL;
		scaled_client_scale = 1.0;
	}
	if (client != NULL) {
		scaled_client = client;
		scaled_client_scale = scale;
		scaled_client_destroy.notify = handle_scaled_client_destroy;
		wl_client_add_destroy_listener(client, &scaled_client_destroy);
	}
}

double wlr_server_scale_get(const struct wl_client *client) {
	if (client != NULL && client == scaled_client) {
		return scaled_client_scale;
	}
	return 1.0;
}
