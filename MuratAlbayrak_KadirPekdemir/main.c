#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <stdbool.h>

#define MAX_CITIES 50000
typedef struct {
    long int city;
    long int x;
    long int y;
} City;
long int calculateDistance(City city1, City city2) {
    long int dx = city1.x - city2.x;
    long int dy = city1.y - city2.y;
    return round(sqrt(dx * dx + dy * dy));

}
int cityVisited(long int cityIndex, int tour[], long int tourSize) {
    for (long int i = 0; i < tourSize; i++) {
        if (tour[i] == cityIndex) {
            return 1;
        }
    }
    return 0;
}

double calculateTourDistance(City cities[], int tour[], long int numCities) {
    double totalDistance = 0.0;
    for (int i = 0; i < numCities -1; i++) {
        int cityIndex1 = tour[i];
        int cityIndex2 = tour[i + 1];
        City city1 = cities[cityIndex1];
        City city2 = cities[cityIndex2];
        totalDistance += calculateDistance(city1, city2);
    }
    // İlk ve son şehir mesafe
    int firstCityIndex = tour[0];
    int lastCityIndex = tour[numCities - 1];
    City firstCity = cities[firstCityIndex];
    City lastCity = cities[lastCityIndex];
    totalDistance += calculateDistance(firstCity, lastCity);
    return totalDistance;
}
void swapCities(int tour[], int i, int j) {
    int temp = tour[i];
    tour[i] = tour[j];
    tour[j] = temp;
}
void generateInitialTour(City cities[], long int numCities, int tour[]) {
    long int closestCityIndex = 0;
    double closestDistance = calculateDistance(cities[0], cities[1]);
    for (long int i = 1; i < numCities; i++) {
        double distance = calculateDistance(cities[0], cities[i]);
        if (distance < closestDistance) {
            closestCityIndex = i;
            closestDistance = distance;
        }
    }
    tour[0] = cities[closestCityIndex].city;
    for (long int i = 1; i < numCities; i++) {
        long int currentCityIndex = closestCityIndex;
        double minDistance = INFINITY;
        for (long int j = 0; j < numCities; j++) {
            double distance = calculateDistance(cities[currentCityIndex], cities[j]);
            if (distance < minDistance && !cityVisited(j, tour, i)) {
                minDistance = distance;
                closestCityIndex = j;
            }
        }
        tour[i] = cities[closestCityIndex].city;
    }
}
double calculateTourDistance1(City cities[], int tour[], long int numCities, double** tourDistances) {
    double distance = 0.0;
    for (int i = 0; i < numCities - 1; i++) {
        distance += calculateDistance(cities[tour[i]], cities[tour[i + 1]]);
    }
    distance += calculateDistance(cities[tour[0]], cities[tour[numCities - 1]]);
    for (int i = 0; i < numCities; i++) {
        for (int j = 0; j < numCities; j++) {
            if (i != j) {
                tourDistances[i][j] = distance;
            }
        }
    }
    return distance;
}
double calculateTourDistanceCache(City cities[], int tour[], long int numCities, double** tourDistances) {
    double distance = 0.0;
    for (int i = 0; i < numCities - 1; i++) {
        distance += tourDistances[tour[i]][tour[i + 1]];
    }
    distance+= tourDistances[tour[0]][tour[numCities - 1]];
    return distance;
}
void findPath(City cities[], int tour[], long int numCities) {
    double** tourDistances = (double**)malloc(numCities * sizeof(double*));
    for (int i = 0; i < numCities; i++) {
        tourDistances[i] = (double*)malloc(numCities * sizeof(double));
    }
    int iterations = 0;
    double bestDistance = calculateTourDistance1(cities, tour, numCities, tourDistances);
    int improved = 1;
    while (improved) {
        improved = 0;
        for (int i = 1; i < numCities - 2; i++) {
            for (int j = i + 1; j < numCities - 1; j++) {
                swapCities(tour, i, j);
                double newDistance = calculateTourDistanceCache(cities, tour, numCities, tourDistances);

                if (newDistance < bestDistance) {
                    bestDistance = newDistance;
                    improved = 1;
                }
                else {
                    swapCities(tour, i, j); // Geri değiştir
                }
                iterations++;
                if (iterations >= numCities/10) {
                    break;
                }
            }
        }
    }
    for (int i = 0; i < numCities; i++) {
        free(tourDistances[i]);
    }
    free(tourDistances);
}

int main() {
    clock_t start = clock();
    City cities[MAX_CITIES];
    long int numCities;
    int tour[MAX_CITIES];
    char input[MAX_CITIES];
    char filename[1000];
    printf("Please enter the filename: \n");
    scanf("%s", filename);

    FILE *file = fopen(filename, "r");

    if (file == NULL) {
        printf("Dosya okunamadı!");
        return 1;
    }
    while (fgets(input, sizeof(input), file)) {
        sscanf(input, "%d %d %d", &cities[numCities].city, &cities[numCities].x, &cities[numCities].y);
        numCities++;
    }
    fclose(file);
    generateInitialTour(cities, numCities, tour);
    findPath(cities, tour, numCities);
    if(numCities % 2 == 0){
        numCities = (long int)(numCities / 2);
    }else{
        numCities = (long int)(numCities / 2 + 1);
    }
    double tourDistance = calculateTourDistance(cities, tour, numCities);

    FILE* output = fopen("output.txt", "w");
    if (output == NULL) {
        printf("Output dosya hatasi açma hatası!\n");
        return 1;
    }
    fprintf(output, "%.lf\n", tourDistance);
    for (long int i = 0; i < numCities; i++) {
        fprintf(output, "%ld\n", tour[i]);
    }
    fclose(output);
    printf("En iyi tur: ");
    for (int i = 0; i < numCities; i++) {
        printf("%d ", tour[i]);
    }
    printf("\nTur uzunluğu: %.f\n", tourDistance);
    clock_t end = clock();
    double elapsed_time = (double)(end - start) / CLOCKS_PER_SEC;
    printf("Kodun çalışma süresi: %.2f saniye\n", elapsed_time);
    return 0;
}

