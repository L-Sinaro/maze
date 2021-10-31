#include "main.h"

int main()
{
    Partition_t partition = creer(11);
    if (partition.tab && partition.hauteur)
    {
        fusionner(partition, 0,1);
        fusionner(partition, 2,3);
        fusionner(partition, 10,3);
        fusionner(partition, 5,9);
        fusionner(partition, 4,6);
        fusionner(partition, 8,7);
        fusionner(partition, 7,9);
        fusionner(partition, 6,8);

        listerClasse(partition, 5);
        listerClasseGraphviz(partition, 5);

        listerPartitions(partition);
        listerPartitionsGraphviz(partition);
    }

    libererPartition(partition);
    return 0;
}