#include <gtk/gtk.h>
#include <stdlib.h>
#include "json-handler.h"

static void execute_command(GtkWidget *widget, gpointer data, char *command) {
    system(command);
    exit(0);
}

gboolean kill_process(GtkWidget *widget, GdkEvent *event, gpointer data) {
    exit(0);
}

int build_buttons(GtkWidget **buttons, int number_of_buttons, GtkCssProvider *css_provider, GtkWidget *button_box) {

    //get json array and parse it
    char * json_object = read_in_object();
    char*** button_elements = parse(json_object);

    char *commands[number_of_buttons];
    char *button_labels[number_of_buttons];

    for (int i= 0;i<6;i++) {
        //paste in commands
        commands[i] = button_elements[i][1];
        //paste in labels
        button_labels[i] = button_elements[i][0];
    }

    for (int i = 0; i < number_of_buttons; i++) {
        buttons[i] = gtk_button_new_with_label(button_labels[i]);
        gtk_style_context_add_provider(gtk_widget_get_style_context(buttons[i]), GTK_STYLE_PROVIDER(css_provider),
                                       GTK_STYLE_PROVIDER_PRIORITY_USER);
        gtk_container_add(GTK_CONTAINER(button_box), buttons[i]);

        g_signal_connect(buttons[i], "clicked", G_CALLBACK(execute_command), commands[i]);
    }
    //free memory from string and string array
    free(json_object);
    free(button_elements);

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
