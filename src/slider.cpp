#include <thread>
#include <functional>

#include <gtk/gtk.h>
#include "slider.h"

bool done = false;

void quit(GtkWidget *, gpointer)
{
  done = true;
  gtk_main_quit();
}

void destroy(GtkWidget *, gpointer window)
{
  gtk_widget_destroy(GTK_WIDGET(window));
}

void run_slider(void)
{
  GtkWidget *window, *box, *slider1, *slider2, *slider3;
  GtkBox *box2;

  gtk_init(NULL, NULL);

  window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
  box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
  slider1 = gtk_scale_new_with_range(GTK_ORIENTATION_HORIZONTAL, 0.0, 1.0, 0.1);
  slider2 = gtk_scale_new_with_range(GTK_ORIENTATION_HORIZONTAL, 0.0, 1.0, 0.1);
  slider3 = gtk_scale_new_with_range(GTK_ORIENTATION_HORIZONTAL, 0.0, 1.0, 0.1);

  box2 = GTK_BOX(box);
  gtk_box_pack_end(box2, slider1, true, true, 0);
  gtk_box_pack_end(box2, slider2, true, true, 0);
  gtk_box_pack_end(box2, slider3, true, true, 0);
  gtk_container_add(GTK_CONTAINER(window), box);

  g_signal_connect(window, "destroy", G_CALLBACK(quit), NULL);

  gtk_widget_show_all(window);
  gtk_main();
}
