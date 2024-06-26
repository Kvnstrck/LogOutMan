#include <gtk/gtk.h>
#include <stdlib.h>

static void execute_command(GtkWidget *widget, gpointer data, char *command) {
    system(command);
    exit(0);
}

gboolean kill_process(GtkWidget *widget, GdkEvent *event, gpointer data) {
    exit(0);
}

int build_buttons(GtkWidget **buttons, int number_of_buttons, GtkCssProvider *css_provider, GtkWidget *button_box) {

    char *commands[number_of_buttons];
    commands[0] = "swaylock";
    commands[1] = "loginctl terminate-user $USER";
    commands[2] = "systemctl poweroff";
    commands[3] = "systemctl reboot";
    commands[4] = "systemctl suspend";
    commands[5] = "systemctl hibernate";

    char *button_labels[number_of_buttons];
    button_labels[0] = "Lock";
    button_labels[1] = "Logout";
    button_labels[2] = "Shutdown";
    button_labels[3] = "Reboot";
    button_labels[4] = "Suspend";
    button_labels[5] = "Hibernate";

    for (int i = 0; i < number_of_buttons; i++) {
        buttons[i] = gtk_button_new_with_label(button_labels[i]);
        gtk_style_context_add_provider(gtk_widget_get_style_context(buttons[i]), GTK_STYLE_PROVIDER(css_provider),
                                       GTK_STYLE_PROVIDER_PRIORITY_USER);
        gtk_container_add(GTK_CONTAINER(button_box), buttons[i]);

        g_signal_connect(buttons[i], "clicked", G_CALLBACK(execute_command), commands[i]);
    }
    return 0;
}

static void activate(GtkApplication *app) {

    GtkWidget *window = gtk_application_window_new(app);
    GtkCssProvider *cssProvider = gtk_css_provider_new();
    GtkWidget *button_box = gtk_button_box_new(GTK_ORIENTATION_VERTICAL);

    //setup window properties
    gtk_window_set_title(GTK_WINDOW(window), "LOGOUT_MAN");
    gtk_window_set_default_size(GTK_WINDOW(window), 120, 300);

    //setup variable for css config
    const char* suffix = "/.config/LogOutMan/main.css";
    const char* config_file = strcat(getenv("HOME"),suffix);

    //setup CSS
    gtk_css_provider_load_from_path(cssProvider, config_file , NULL);
    gtk_style_context_add_provider(gtk_widget_get_style_context(window), GTK_STYLE_PROVIDER(cssProvider),
                                   GTK_STYLE_PROVIDER_PRIORITY_USER);

    //build buttons
    int number_of_buttons = 6;
    GtkWidget *buttons[6];
    build_buttons(buttons, number_of_buttons, cssProvider, button_box);

    //adding and showing the window
    gtk_container_add(GTK_CONTAINER(window), button_box);
    gtk_widget_grab_focus(window);
    gtk_widget_show_all(window);

    //intercept closing of window and kill process
    g_signal_connect(G_OBJECT(window),
                     "delete-event", G_CALLBACK(kill_process), NULL);

    gtk_main();
}

int main(int argc, char *argv[]) {
    GtkApplication *app;
    int status;
    gtk_init(&argc, &argv);
    app = gtk_application_new("org.gtk.example", G_APPLICATION_DEFAULT_FLAGS);
    g_signal_connect(app, "activate", G_CALLBACK(activate), NULL);
    status = g_application_run(G_APPLICATION(app), argc, argv);
    g_object_unref(app);
    return status;
}
