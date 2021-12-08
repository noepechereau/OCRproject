
#include <gtk/gtk.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "../image_system/image_manipulation.h"
#include "../image_system/color_system.h"
#include "../image_system/image_system.h"
#include "../useful/basics.h"
#include "../rotation/rotation.h"




GtkWidget *window;
GtkWidget *button1;
GtkWidget *button2;
GtkWidget *button3;
GtkWidget *expand1;
GtkWidget *button5;
GtkWidget *fixed1;
GtkWidget *image1;
GtkWidget *image2;
GtkWidget *file_opener;
GtkWidget *image_ocr;
GtkScale *scale;
GtkWidget *image3;
GtkWidget *button4;
GtkWidget *image4;



GtkBuilder *builder;

void on_file_opener_file_set(GtkFileChooserButton *f)
{
    gchar *filename = gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(f));
    int h = 200, v= 100;
    if(image1)
    {
        gtk_container_remove (GTK_CONTAINER (fixed1), image1);
    }
    gtk_widget_hide(image2);
    image1 = gtk_image_new_from_file(filename);
    gtk_container_add(GTK_CONTAINER(fixed1),image1);
    gtk_widget_show(image1);

    gtk_fixed_move (GTK_FIXED(fixed1), image1, h, v);
    SDL_Surface *image = Image_Load(filename);
    Image_Rotate(image,gtk_scale_get_digits (scale));
    SDL_SaveBMP_RW(image, SDL_RWFromFile("rotate.bmp","w"),1);
    ApplyCorrection(image);
    SDL_SaveBMP_RW(image, SDL_RWFromFile("binarize.bmp","w"),1);
    ///Image_Rotate(image,gtk_scale_get_digits (scale));
    ///SDL_SaveBMP_RW(image, SDL_RWFromFile("rotate.bmp","w"),1);

}

void on_button2_clicked(GtkButton *b)
{
    b = b;
    char filename[] = "rotate.bmp";
    int h = 200, v = 100;
    if(image3)
    {
        gtk_container_remove (GTK_CONTAINER (fixed1), image3);
    }
    gtk_widget_hide(image1);
    image3 = gtk_image_new_from_file(filename);
    gtk_container_add(GTK_CONTAINER(fixed1),image3);
    gtk_widget_show(image3);

    gtk_fixed_move (GTK_FIXED(fixed1), image3, h, v);
}

void on_button1_clicked(GtkButton *b)
{
    b = b;
    int h = 200, v= 100;
    gtk_widget_hide(image3);
    gtk_container_add(GTK_CONTAINER(fixed1),image1);
    gtk_widget_show(image1);

    gtk_fixed_move (GTK_FIXED(fixed1), image1, h, v);
}
void on_button3_clicked(GtkButton *b)
{
    b = b;
    char filename[] = "binarize.bmp";
    int h = 400, v = 250;
    if(image4)
    {
        gtk_container_remove (GTK_CONTAINER (fixed1), image4);
    }
    gtk_widget_hide(image3);
    image3 = gtk_image_new_from_file(filename);
    gtk_container_add(GTK_CONTAINER(fixed1),image4);
    gtk_widget_show(image4);

    gtk_fixed_move (GTK_FIXED(fixed1), image4, h, v);
}

int main (int argc, char *argv[])
{
    gtk_init(&argc,&argv);
    builder = gtk_builder_new_from_file ("ocr.glade");
    window = GTK_WIDGET(gtk_builder_get_object(builder, "Window"));
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);
    gtk_builder_connect_signals(builder, NULL);

    button1 = GTK_WIDGET(gtk_builder_get_object(builder, "button1"));
    button2 = GTK_WIDGET(gtk_builder_get_object(builder, "button2"));
    button3 = GTK_WIDGET(gtk_builder_get_object(builder, "button3"));
    expand1 = GTK_WIDGET(gtk_builder_get_object(builder, "expand1"));
    button5 = GTK_WIDGET(gtk_builder_get_object(builder, "button5"));
    file_opener = GTK_WIDGET(gtk_builder_get_object(builder, "file_opener"));
    fixed1 = GTK_WIDGET(gtk_builder_get_object(builder, "fixed1"));
    scale = GTK_SCALE(gtk_builder_get_object(builder, "scale"));
    button4 = GTK_WIDGET(gtk_builder_get_object(builder, "button4"));

    gtk_range_set_range(GTK_RANGE(scale), 0, 360);

    g_signal_connect(file_opener, "clicked", G_CALLBACK(on_file_opener_file_set), NULL);
    g_signal_connect(button1, "clicked", G_CALLBACK(on_button1_clicked), NULL);
    g_signal_connect(button2, "clicked", G_CALLBACK(on_button2_clicked), NULL);
    g_signal_connect(button3, "clicked", G_CALLBACK(on_button3_clicked), NULL);
    //g_signal_connect(scale,"change-value",G_CALLBACK(save_degree),NULL);

    gtk_widget_show(window);
    gtk_main();

    return EXIT_SUCCESS;
}
