/*file:///home/t/Documents/FFT_lib/main.cpp

----- Tuto makefile : fichier main
*/




//définition des dépendances
#include <iostream>
#include "FFTlib.h"
#include <chrono>
#include <math.h>

int main(void)
{
    std::cout << "----Bienvenue dans l'exemple de FFTlib----" << std::endl;
    std::cout << "Creation des paramètres" << std::endl;
    //définition des paramètres
    int int_part, tab[2]={1000,2000}; // valeur de retour pour la fonction computeNT
    std::cout << "1" << std::endl;
    std::complex<float> *sig_in = (std::complex<float> *) malloc(sizeof(std::complex<float>) * 12000001); // Allocation mémoir du signal d'entrée de type complexe
    std::complex<float> *tf_out = (std::complex<float> *) malloc(sizeof(std::complex<float>) * 12000001); // Allocation mémoir du signal de sortie de type complexe
    std::cout << "2" << std::endl;
    // Implémentation du signal d'entrée
    for( int i =0 ; i < 12000000 ; i++ )
    {
        sig_in[i].real(std::cos(800*M_PI*i/1000) + std::cos(1600*M_PI*i/1000) );
        sig_in[i].imag(std::sin(800*M_PI*i/1000) + std::cos(1600*M_PI*i/1000) );
    }
    std::cout << "Creation des paramètres terminé" << std::endl;
    FFTlib f; // Constructeur de l'objet FFTlib
    std::cout << "Creation de l'objet FFTlib terminé" << std::endl;
    f.Init( 2 , tab ); // Init() de la classe FFTlib
    std::cout << "Initialisation des paramètres terminé" << std::endl;
    int_part = f.ComputeNT(
            12000000,
            1000,
            1,
            1000); // computeNT de la classe FFTlib
    std::cout << "Calcul du nombre d'échantillon terminé" << std::endl;
    auto start = std::chrono::steady_clock::now();
    f.Execute(
            tf_out,
            sig_in,
            12000000,
            1000,
            1000,
            1,
            0); // Execute de la classe FFTlib

    auto end = std::chrono::steady_clock::now();
    std::chrono::duration<double> elapsed_seconds = end - start;
    std::cout << "time :" << elapsed_seconds.count() << std::endl;
    for( int i = 0 ; i< 1000 ; i++)
    {
        std::cout << "Fréquence [" << i << "] : " << std::abs(tf_out[i]) << std::endl;
    }

}
