#include <iostream>
#include <cstring>
using std::cout, std::cin, std::endl;
const short MAX_NAME_SIZE = 100;

enum Genre
{
    Comedy,
    Action,
    Horror,
    Romantic
};

struct Movie
{
    char name[MAX_NAME_SIZE + 1];
    unsigned short length;
    Genre genre;
    double rating;
};

void createMovie(Movie& movie, const char* name, unsigned short length, Genre genre, double rating)
{
    strcpy_s(movie.name, MAX_NAME_SIZE, name);
    movie.length = length;
    movie.genre = genre;
    movie.rating = rating;
}

void printMovie(const Movie& movie)
{
    cout << endl;
    cout << "---------Movie---------"<< endl;
    cout << "Name: " << movie.name << endl;
    cout << "Length in minutes: " << movie.length << endl;
    switch (movie.genre)
    {
    case 0:
        cout << "Genre: Comedy" << endl;
        break;
    case 1:
        cout << "Genre: Action" << endl;
        break;
    case 2:
        cout << "Genre: Horror" << endl;
        break;
    case 3:
        cout << "Genre: Romantic" << endl;
        break;
    }
    cout << "Rating: " << movie.rating << endl;
    cout << endl;
}

Movie highestRated (Movie* movies, int numberOfMovies)
{
    size_t highestRatedMovie = 0;
    double maxRating = movies[0].rating;
    for (size_t i = 1; i < numberOfMovies; i++)
    {
        if (maxRating < movies[i].rating)
        {
            highestRatedMovie = i;
        }
        
    }
    return movies[highestRatedMovie];
}

void sortMovies(Movie* movies, int numberOfMovies)
{
    if (numberOfMovies == 0)
    {
        return;
    }
    movies[0] = highestRated(movies, numberOfMovies);
    sortMovies(movies + 1, numberOfMovies - 1);
}

int main()
{
    int numberOfMovies;
    cout << "Number of movies: ";
    cin >> numberOfMovies;
    Movie* movies = new Movie[numberOfMovies];
    for (size_t i = 0; i < numberOfMovies; i++)
    {
        cout << "Movie "<<i + 1<<":"<<endl;
        char name[MAX_NAME_SIZE + 1];
        cout << "Name: ";
        cin.ignore();
        cin.getline(name, MAX_NAME_SIZE + 1);
        unsigned short length;
        cout << "Length: ";
        cin >> length;
        int genreAsInt;
        cout << "Genre: ";
        cin >> genreAsInt;
        Genre genre = (Genre)genreAsInt;
        double rating;
        cout << "Rating: ";
        cin >> rating;
        createMovie(movies[i], name, length, genre, rating);
    }
    sortMovies(movies, numberOfMovies);
    for (size_t i = 0; i < numberOfMovies; i++)
    {
        printMovie(movies[i]);
    }
    cout << "The highest rated movie is: "<< endl;
    printMovie(highestRated(movies, numberOfMovies));

}