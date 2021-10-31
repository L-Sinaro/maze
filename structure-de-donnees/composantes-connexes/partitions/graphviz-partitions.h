#ifndef GRAPHVIZ_PARTITION_H
#define GRAPHVIZ_PARTITION_H

#include <stdio.h>
#include <stdlib.h>
#include <graphviz/gvc.h>
#include <graphviz/cgraph.h>
#include "partitions.h"
#include "liste-chainee.h"


int listerClasseGraphviz(Partition_t partition, int etiquette);
int listerPartitionsGraphviz(Partition_t partition);

#endif 