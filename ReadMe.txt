Ce fichier décrit l'installation de la librairie FFTlib ainsi que ces dépendances.

l'installation de FFTlib dépends de plusieurs lib de linux :
- CMAKE
- FFTW3
- GIT
- G++

Commande Linux installation :

cmake :	apt-get install cmake
git   : apt-get install git
G++   : apt-get install vim g++ codelite cmake

Pour FFTW3, le fichier fftw-3.3.9.tar.gz va nous permettre d'installer FFTW3.
Dans un premier temps, on extrait le fichier de l'archive.
Nous allons ensuite faire les commandes suivantes dans le dossier fftw-3.3.9:

./configure
make 
make install 
make clean
./configure --enable-float
make 
make install 

Maintenant il va nous manquer le fichier indiquant les dépendances de la librairie FFTW3.
Il se trouve aussi dans le dossier dépendances : FFTW3LibraryDepends.cmake .
Il faut le copier dans le dossier /usr/local/lib/cmake/fftw3.

exemple : Si on se trouve dans le dossier Documents/FFTlib/Dépendances 
cp FFTW3LibraryDepends ../../../../../usr/local/lib/cmake/fftw3

Maintenant, il nous manque juste à faire le cmake de FFTlib.
On crée un fichier build et on se rend dedans : mkdir build && cd build 
Maintenant on lance le cmake et on l'install :

cmake ..
make 
make install 

Et voila ! 
Tout est installé.
 

