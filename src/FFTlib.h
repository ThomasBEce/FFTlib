#ifndef FFTLIB_H
#define FFTLIB_H

#include <vector>
#include <cmath>

#include <fftw3.h>
#include <complex>

class FFTlib
{
    public:
        FFTlib();
        virtual ~FFTlib();
        void Init(int nb_param, int tab_param[]);
        int ComputeNT(int nb_ech, int nb_fft, int decalage_t, int nfft);

        void Execute(std::complex<float> *tf_out, std::complex<float> *sig_in, int nb_ech_in, int nfft, int decalage, int nb_voies, int nt_max);

    private:
        int nb_param;
        std::vector<int> tab_param;
        int NT_intpart;
        fftwf_plan p;
        std::vector<std::vector<float>> tab_ponde;
        std::vector<std::complex<float>> in_fft;

};

#endif // FFTLIB_H
