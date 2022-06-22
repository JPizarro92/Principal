#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp> // Interfaz gráfica de usuario
#include <opencv2/imgproc/imgproc.hpp> // Procesamiento de imágenes
#include <opencv2/imgcodecs/imgcodecs.hpp> // Códecs para leer los distintos formatos de imágenes (JPG, PNG, etc.)
#include <opencv2/video/video.hpp> // Lectura de vídeos
#include <opencv2/videoio/videoio.hpp> // Lectura y escritura de videos
#include <opencv2/objdetect/objdetect.hpp> // Para realizar detección de objetos

using namespace std;
using namespace cv;

int main(int argc, char *argv[]) {
    Mat imgEjercicio = imread("./Ejercicios/MANUELA_SAENZ.png");
    Mat imgOriginal = imread("./Originales/MANUELA_SAENZ.png");
    Mat imgResultado (Size(imgEjercicio.cols,imgEjercicio.rows), CV_8UC3, Scalar(255,255,255));
    
    Vec3b pixelColor;
    Vec3b pixel;
    int bandera = 0;
    
    for (int i = 0; i < imgEjercicio.rows; i++) {
        bandera = 0;
        for (int j = 0; j < imgEjercicio.cols; j++) {
            if (imgEjercicio.at<Vec3b>(i, j) != imgOriginal.at<Vec3b>(i, j)) {
                pixelColor = imgEjercicio.at<Vec3b>(i, j);
                int inicio = j;
                int fin = j;
                for (int p = j; p < imgEjercicio.cols; p++) {
                    if (imgEjercicio.at<Vec3b>(i, p) == pixelColor) {
                        //cout << "Fila " << i << " - Columna " << p << endl;
                        fin = p;
                    }
                }
                for (int p = j; p < imgEjercicio.cols; p++) {
                    pixel = imgOriginal.at<Vec3b>(i, p);
                    if (p <= fin) {
                        imgResultado.at<Vec3b>(i,p) = Vec3b(255 - pixel[0], 255 - pixel[1], 255 - pixel[2]);
                    }
                    else {
                        imgResultado.at<Vec3b>(i, p) = pixel;
                    }
                }
                
                break;
            }
            else {
                imgResultado.at<Vec3b>(i, j) = imgOriginal.at<Vec3b>(i, j);
            }
        }

    }
    imwrite("Original.png", imgOriginal);
    imwrite("Ejercicio.png", imgEjercicio);
    imwrite("Resultado.png", imgResultado);
    namedWindow("Original", WINDOW_AUTOSIZE);
    namedWindow("Ejercicio", WINDOW_AUTOSIZE);
    namedWindow("Resultado", WINDOW_AUTOSIZE);
    imshow("Original", imgOriginal);
    imshow("Ejercicio", imgEjercicio);
    imshow("Resultado", imgResultado);
    waitKey(0);
	return 0;
}