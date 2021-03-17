#include "FFTlib.h"
#include <iostream>
#include <vector>
using namespace std;

FFTlib::FFTlib()
{
    //ctor
    std::cout<<"L'Objet FFTlib est créé."<< endl;
}

FFTlib::~FFTlib()
{
    //dtor
    std::cout<<"L'Objet FFTlib est détruit."<< endl;
    fftwf_destroy_plan(this->p);
}

/* Fonction d'initialisation de la classe FFTlib
    in : nombre de paramètre + tableau avec les paramètres
    out : tableau fenêtre de pondération + fenêtre fft
*/
void FFTlib::Init( int nb_param , int tab_param[] )
{
    std::cout << "On entre dans la Fontion Init." << endl;
    this->nb_param = nb_param;
    int val;
	for( int i =0 ; i < nb_param ; i++ ) // faire pour chaque paramètre fen pondé et fen FFT
	{
        val = tab_param[i];
		this->tab_param.push_back( val ); // ajout des paramètres dans un tableau
		this->tab_ponde.push_back( vector<float>( val ) ); // Ajout d'une fen de pondé pour chaque paramètre
        std::cout<<"Tableau de pondération : " << i << endl ;
		for( int j =0 ; j < tab_param[i] ; j++ ) // pour chaque point calculer la valeur de pondé
		{
			this->tab_ponde[i][j] = 0.5*(1-cos((2*M_PI*j)/(float)tab_param[i]));
			//std::cout << "Val " << j << "= " << this->tab_ponde[i][j] << endl ;
		}
    }
    std::cout << "On sort de la fontion Init." << std::endl;
}

/*
Compute NT : calcule le nombre de FFT pour une voie
    in : nombre d'échantillon , taille de la fft, nombre de fft, décalage tempo
    out : nombre de fft pour une voie
*/

int FFTlib::ComputeNT( int nb_ech , int nfft , int nb_fft , int decalage_t )
{
    std::cout<<"On entre dans la fonction ComputeNT" << endl ;

    //déclaration des variables
	double NT_t,NT_intpart_p , NT_doublepart_p; // déclaration des variables
	//calcule
	NT_t = (nb_ech - ( nfft * nb_fft)) /decalage_t; // calcule du nombre de fft
	NT_doublepart_p = modf(NT_t, &NT_intpart_p); // séparation en parties entières
	NT_intpart = (int)NT_intpart_p;

	//mise à l'échelle du tableau intermédiaire de calcul
	this->in_fft.resize(nfft);

	//initialisation du plan de calcul fft
	this->p = fftwf_plan_dft_1d( nfft , NULL , NULL , FFTW_FORWARD , FFTW_ESTIMATE );

	//retour de la valeur Nombre d'échantillons
	//std::cout << "Sortie de la fontion ComputeNT : " << NT_intpart_p << ". On perd " << NT_doublepart_p <<" echantillons" <<  endl ;
	return NT_intpart; // retour de la valeur entière
}

/*
Execute : Execute les FFT
    in : pointeur de sortie, pointeur d'entré, bombre d'échantillon en entré, nombre de voie, taille des fft, décalage, nombre de fft, temps max
    out : tableau de toutes les fft
*/
void FFTlib::Execute( std::complex<float> *tf_out,
                      std::complex<float> *sig_in,
                      int nb_ech_in,
                      int nfft,
                      int decalage,
                      int nb_voies,
                      int nt_max)
{
    std::cout << "On entre dans la fonction Execute" << endl ;
    //déclaration des variables
	int i , j , e , a ;
	int lim_left;
	int point , ech ;
	float R, Im;

    int nb_ech_total = (this->NT_intpart) * nb_voies;
    for( i = 0 ; i < this->nb_param ; i++)
    {
        if (this->tab_param[i] == nfft){break;}
    }
    //découpe des échantillons
    for( ech = 0 ;
         ech < nb_ech_total ;
         ech++ )
    {
        for( e = 0 ; e < nfft ; e++ )
        {
            a = e + decalage * ech ;
            R = (sig_in[a].real() * this->tab_ponde[i][e]);
            Im = (sig_in[a].imag() * this->tab_ponde[i][e]);
            in_fft[e].real(R);
            in_fft[e].imag(Im);
            //std::cout << "resultat : " << test << std::endl;
        }

        point = ech*nfft;
        fftwf_execute_dft(this->p , reinterpret_cast<fftwf_complex*>(&in_fft[0]) , reinterpret_cast<fftwf_complex*>(&tf_out[point]) );
    }
    //std::cout << "Fin de la Fonction Execute." << std::endl;
}
