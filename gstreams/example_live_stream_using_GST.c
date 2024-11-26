#include <gst/gst.h>

int main (int argc, char *argv[])
{
  GstElement *pipeline;
  GstBus *bus;
  GstMessage *msg;

  /* Initialize GStreamer */
  gst_init (&argc, &argv);

  /* Create pipeline to access the camera feed */
  pipeline = gst_parse_launch (
      "v4l2src device=/dev/video0 ! videoconvert ! autovideosink", NULL);

  if (!pipeline) {
    g_printerr ("Failed to create pipeline. Check your device and permissions.\n");
    return -1;
  }

  /* Start the pipeline */
  gst_element_set_state (pipeline, GST_STATE_PLAYING);

  /* Wait for EOS or error */
  bus = gst_element_get_bus (pipeline);
  msg = gst_bus_timed_pop_filtered (bus, GST_CLOCK_TIME_NONE,
                                    GST_MESSAGE_ERROR | GST_MESSAGE_EOS);

  if (GST_MESSAGE_TYPE (msg) == GST_MESSAGE_ERROR) {
    GError *err;
    gchar *debug_info;

    gst_message_parse_error (msg, &err, &debug_info);
    g_printerr ("Error: %s\n", err->message);
    g_printerr ("Debug info: %s\n", debug_info ? debug_info : "none");
    g_clear_error (&err);
    g_free (debug_info);
  }

  /* Free resources */
  gst_message_unref (msg);
  gst_object_unref (bus);
  gst_element_set_state (pipeline, GST_STATE_NULL);
  gst_object_unref (pipeline);

  return 0;
}

