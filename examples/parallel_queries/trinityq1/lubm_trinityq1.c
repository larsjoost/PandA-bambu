#include <stdio.h>
#include "simple_API.h"

// p_var_3 = "ub:subOrganizationOf"
// var_4 = "ub:University"
// p_var_5 = "a"
// p_var_6 = "ub:Department"
// p_var_7 = "a"
// p_var_9 = "ub:memberOf"
// p_var_10 = "ub:GraduateStudent"
// p_var_11 = "a"
// p_var_12 = "ub:undergraduateDegreeFrom"

__attribute__((noinline))
void kernel(size_t i_var_5, Graph * graph, NodeId var_4, PropertyId p_var_3, PropertyId p_var_5, PropertyId p_var_6, PropertyId p_var_7, PropertyId p_var_9, PropertyId p_var_10, PropertyId p_var_11, PropertyId p_var_12, size_t in_degree_var_4, Edge * var_4_1_inEdges)
{
  unsigned localCounter = 0;
  PropertyId var_5;  //corresponding to element having label "a"
  var_5 = var_4_1_inEdges[i_var_5].property;
  NodeId var_2; //corresponding to element having label "?Y"
  var_2 = var_4_1_inEdges[i_var_5].node;
  int  cond_level_2 = (var_5 == p_var_5);
  if(cond_level_2)
  {
    size_t in_degree_var_2 = getInDegree(graph, var_2);
    Edge * var_2_3_inEdges = getInEdges(graph, var_2);
    size_t i_var_3;
    for(i_var_3=0; i_var_3 < in_degree_var_2; i_var_3++)
    {
      PropertyId var_3;  //corresponding to element having label "ub:subOrganizationOf"
      var_3 = var_2_3_inEdges[i_var_3].property;
      NodeId var_1; //corresponding to element having label "?Z"
      var_1 = var_2_3_inEdges[i_var_3].node;
      int  cond_level_4 = (var_3 == p_var_3);
      if(cond_level_4)
      {
        size_t in_degree_var_1 = getInDegree(graph, var_1);
        Edge * var_1_5_inEdges = getInEdges(graph, var_1);
        size_t i_var_9;
        for(i_var_9=0; i_var_9 < in_degree_var_1; i_var_9++)
        {
          PropertyId var_9;  //corresponding to element having label "ub:memberOf"
          var_9 = var_1_5_inEdges[i_var_9].property;
          NodeId var_8; //corresponding to element having label "?X"
          var_8 = var_1_5_inEdges[i_var_9].node;
          int  cond_level_6 = (var_9 == p_var_9);
          if(cond_level_6)
          {
            size_t out_degree_var_8 = getOutDegree(graph, var_8);
            Edge * var_8_7_outEdges = getOutEdges(graph, var_8);
            size_t i_var_11;
            for(i_var_11=0; i_var_11 < out_degree_var_8; i_var_11++)
            {
              PropertyId var_11;  //corresponding to element having label "a"
              var_11 = var_8_7_outEdges[i_var_11].property;
              NodeId  var_10;   //corresponding to element having label "ub:GraduateStudent"
              var_10 = var_8_7_outEdges[i_var_11].node;
              int  cond_level_8 = ((var_11 == p_var_11) & (var_10 == p_var_10));
              if(cond_level_8)
              {
                size_t out_degree_var_1 = getOutDegree(graph, var_1);
                Edge * var_1_9_outEdges = getOutEdges(graph, var_1);
                size_t i_var_7;
                for(i_var_7=0; i_var_7 < out_degree_var_1; i_var_7++)
                {
                  PropertyId var_7;  //corresponding to element having label "a"
                  var_7 = var_1_9_outEdges[i_var_7].property;
                  NodeId  var_6;   //corresponding to element having label "ub:Department"
                  var_6 = var_1_9_outEdges[i_var_7].node;
                  int  cond_level_10 = ((var_7 == p_var_7) & (var_6 == p_var_6));
                  if(cond_level_10)
                  {
                    Edge * var_2_11_inEdges = getInEdges(graph, var_2);
                    size_t i_var_12;
                    for(i_var_12=0; i_var_12 < in_degree_var_2; i_var_12++)
                    {
                      PropertyId var_12;  //corresponding to element having label "ub:undergraduateDegreeFrom"
                      var_12 = var_2_11_inEdges[i_var_12].property;
                      NodeId var_8_12; //corresponding to element having label "?X"
                      var_8_12 = var_2_11_inEdges[i_var_12].node;
                      int  cond_level_12 = ((var_12 == p_var_12) & (var_8_12 == var_8));
                      if(cond_level_12)
                      {
                        // here the "required" results are written (if any)
                        localCounter++;
                      }
                    }
                  }
                }
              }
            }
          }
        }
      }
    }
    atomicIncrement(&(counter[i_var_5 % N_THREADS]), localCounter);
  }
}


__attribute__((noinline))
void parallel(Graph * graph, NodeId var_4, PropertyId p_var_3, PropertyId p_var_5, PropertyId p_var_6, PropertyId p_var_7, PropertyId p_var_9, PropertyId p_var_10, PropertyId p_var_11, PropertyId p_var_12, size_t in_degree_var_4, Edge * var_4_1_inEdges)
{
  size_t i_var_5;
#pragma omp parallel for
  for(i_var_5=0; i_var_5 < in_degree_var_4; i_var_5++)
  {
    kernel(i_var_5, graph, var_4, p_var_3, p_var_5, p_var_6, p_var_7, p_var_9, p_var_10, p_var_11, p_var_12, in_degree_var_4, var_4_1_inEdges);
  }
}

__attribute__((noinline))
int search(Graph * graph, NodeId var_4, PropertyId p_var_3, PropertyId p_var_5, PropertyId p_var_6, PropertyId p_var_7, PropertyId p_var_9, PropertyId p_var_10, PropertyId p_var_11, PropertyId p_var_12)
{
  size_t in_degree_var_4 = getInDegree(graph, var_4);
  printf("In degree %d\n", in_degree_var_4);
  Edge * var_4_1_inEdges = getInEdges(graph, var_4);
  parallel(graph, var_4, p_var_3, p_var_5, p_var_6, p_var_7, p_var_9, p_var_10, p_var_11, p_var_12, in_degree_var_4, var_4_1_inEdges);

  for (int i = 0; i < N_THREADS; ++i)
    numAnswers += counter[i];
   return numAnswers;
}

int test(NodeId var_4, PropertyId p_var_3, PropertyId p_var_5, PropertyId p_var_6, PropertyId p_var_7, PropertyId p_var_9, PropertyId p_var_10, PropertyId p_var_11, PropertyId p_var_12)
{
#if defined(DATASETInVertexFile) && defined(DATASETOutVertexFile) && defined(DATASETInEdgeFile) && defined(DATASETOutEdgeFile)
  loadGraph(DATASETInVertexFile, DATASETOutVertexFile, DATASETInEdgeFile, DATASETOutEdgeFile);
#else
  //loadGraph("dataset/40-InVertexFile.bin", "dataset/40-OutVertexFile.bin", "dataset/40-InEdgeFile.bin", "dataset/40-OutEdgeFile.bin");
  loadGraph("dataset/1-InVertexFile.bin", "dataset/1-OutVertexFile.bin", "dataset/1-InEdgeFile.bin", "dataset/1-OutEdgeFile.bin");
#endif

// p_var_3 = "ub:subOrganizationOf" 5
// var_4 = "ub:University" 11347
// p_var_5 = "a" 14
// p_var_6 = "ub:Department" 11412
// p_var_7 = "a" 14
// p_var_9 = "ub:memberOf" 4
// p_var_10 = "ub:GraduateStudent" 20133
// p_var_11 = "a" 14
// p_var_12 = "ub:undergraduateDegreeFrom" 6
  int ret_value = search(&TheGraph, var_4, p_var_3, p_var_5, p_var_6, p_var_7, p_var_9, p_var_10, p_var_11, p_var_12);
  printf("%d\n", ret_value);
  return ret_value;
}


#ifdef DEBUG
int main() {
  //return test(922492, 16, 12, 760360, 12, 13, 1006845, 12, 11) != 106;
  return test(1685, 14, 10, 1828, 10, 4, 7672, 10, 3) != 0;
}
#endif
