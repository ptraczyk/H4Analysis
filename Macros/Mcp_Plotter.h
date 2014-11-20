#include <stdlib.h>
#include <string>
#include <iostream>
#include <cstring>
#include <sstream>
#include <vector>


enum BOX { ON, OFF };

struct MCP{//map that connect RUN number to the informations on one MCP
  map<int,int> pos;
  map<int,int> hv;
  map<int,int> x0;
  map<int,int> pc;
  map<int,int> box;
};

struct MCP_Pos{//It countain all the informations of the RUN on all the MCPs
 MCP SEE;
 MCP MIB2;
 MCP MIB3;
 MCP Z1;
 MCP Z2;
};


void InitMCP_Pos( MCP_Pos &a ){

  int RUN_List[11]={738,739,740,741,742,743,744,745,746,747,748};
  for(int i=0; i<11; i++){
    a.SEE.pos[ RUN_List[i] ] = 0;  a.SEE.box[ RUN_List[i] ] = ON;  a.SEE.pc[ RUN_List[i] ] = ON;  
    a.Z1.pos[ RUN_List[i] ] = 1;   a.Z1.box[ RUN_List[i] ] = ON;   a.Z1.pc[ RUN_List[i] ] = ON;
    a.Z2.pos[ RUN_List[i] ] = 2;   a.Z2.box[ RUN_List[i] ] = ON;   a.Z2.pc[ RUN_List[i] ] = ON;
    a.MIB2.pos[ RUN_List[i] ] = 3; a.MIB2.box[ RUN_List[i] ] = ON; a.MIB2.pc[ RUN_List[i] ] = ON;
    a.MIB3.pos[ RUN_List[i] ] = 4; a.MIB3.box[ RUN_List[i] ] = ON; a.MIB3.pc[ RUN_List[i] ] = ON;
  }
// 738            2200                 3300              3300            3300             11k
// 739            2100                 3200              3200            3200             10k
// 740            2000                 3100              3100            3100             14K  
// 741            1900                 3000              3000            3000             11K  
// 742            1800                 2900              2900            2900             10K
// 743            1700                 2800              2800            2800             10.5K
// 744            1600                 2700              2700            2700             11.7K
// 745            1500                 2600              2600            2600             10.5K
// 746            1400                 2500              2500            2500             10.1K
// 747            1300                 2400              2400            2400             10.1K
// 748            1200                 2300              2300            2300             11K  
}
