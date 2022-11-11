/* K-Means image segmentation
 *
 * This program only works with uncompressed images
 * PPM with type P3
 */

#include "image.h"
#include <iostream>
#include <string>
#include <ctime>
#include <cstdlib>
#include <vector>

using namespace std;

int main()
{
    // Set the seed for better random generation
    srand(time(NULL));

    // Get the path of the original image
    string imageDir;
    cout << "Image path: ";
    cin >> imageDir;
    Image* image(new Image(imageDir));

    // Get the path of the image to save
    string saveImageAs;
    cout << "Save image as: ";
    cin >> saveImageAs;

    // Create each cluster
    int clusterCount;
    cout << "How many colours? ";
    cin >> clusterCount;
    vector<Cluster*> clusters;
    for (int i(0); i < clusterCount; i++)
    {
        clusters.push_back(new Cluster(image));
    }

    // Get the threshold
    double threshold;
    cout << "Threshold: ";
    cin >> threshold;

    // Repeat the algorithm until the average centroid change goes below the threshold
    double averageCentroidChange;
    do
    {
        // Clear all pixels for each cluster
        for (int i(0); i < clusterCount; i++)
        {
            clusters[i]->clearPixels();
        }

        // Go through each pixel in the image
        for (int i(0); i < image->getLength(); i++)
        {
            // Calculate which cluster centroid the pixel is nearest to
            int closestClusterIndex(0);
            double dist;
            for (int j(0); j < clusters.size(); j++)
            {
                dist = clusters[j]->getDistanceTo(image->getPixel(i));
                if (dist < clusters[closestClusterIndex]->getDistanceTo(image->getPixel(i)))
                {
                    closestClusterIndex = j;
                }
            }

            // Add the pixel to the nearest cluster
            clusters[closestClusterIndex]->addPixel(image->getPixel(i));
        }

        // Calculate the average change of the centroids
        averageCentroidChange = 0;
        for (int i(0); i < clusters.size(); i++)
        {
            averageCentroidChange += clusters[i]->adjustCentroid();
        }
        averageCentroidChange /= clusters.size();
        cout << "Average centroid change: " << averageCentroidChange << endl;
    } while (averageCentroidChange > threshold);

    // Change all pixels to the color of the corresponding cluster centroid
    for (int i(0); i < clusters.size(); i++)
    {
        clusters[i]->changeAll();
    }

    // Save the new image
    image->saveImage(saveImageAs);

    return 0;
}