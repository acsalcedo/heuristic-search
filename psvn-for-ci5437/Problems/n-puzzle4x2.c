#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#define __STDC_FORMAT_MACROS
#define __STDC_LIMIT_MACROS
#include <inttypes.h>
#include <string.h>
#include <assert.h>
#include <ctype.h>


#define psvn2c_PSVN_API

#define HAVE_FWD_MOVE_PRUNING
#define HAVE_BWD_MOVES
#define HAVE_BWD_MOVE_PRUNING
#define HAVE_ABSTRACTION


/* number of variables in a state */
#define NUMVARS 16


typedef int8_t var_t;
#define PRI_VAR PRId8
#define SCN_VAR SCNd8

#define NUMDOMAINS 1
static var_t domain_sizes[ NUMDOMAINS ] = { 16 };
static const char *name_of_domain[ NUMDOMAINS ] = { "TILE" };
static int var_domains[ NUMVARS ] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
static const char *domain_0[ 16 ] = {"B", "1", "2", "4", "3", "5", "6", "7", "8", "9", "10", "11", "12", "13", "14", "15" };
static const char **domain_to_domain_names[ NUMDOMAINS ] = { domain_0 };
static const char **var_domain_names[ NUMVARS ] = { domain_0, domain_0, domain_0, domain_0, domain_0, domain_0, domain_0, domain_0, domain_0, domain_0, domain_0, domain_0, domain_0, domain_0, domain_0, domain_0 };

typedef struct {
 var_t vars[ NUMVARS ];
} state_t;

typedef int (*funcptr)( const state_t *, void * );
typedef void (*actfuncptr)( const state_t *, state_t * );

typedef struct {
 const state_t *my_state;
 funcptr my_funcptr;
} ruleid_iterator_t;

#define num_fwd_rules 48
#define num_bwd_rules 48
static const char *fwd_rule_name[ 48 ] = { "LEFT", "RIGHT", "LEFT", "RIGHT", "LEFT", "RIGHT", "LEFT", "RIGHT", "LEFT", "RIGHT", "LEFT", "RIGHT", "LEFT", "RIGHT", "LEFT", "RIGHT", "LEFT", "RIGHT", "LEFT", "RIGHT", "LEFT", "RIGHT", "LEFT", "RIGHT", "UP", "DOWN", "UP", "DOWN", "UP", "DOWN", "UP", "DOWN", "UP", "DOWN", "UP", "DOWN", "UP", "DOWN", "UP", "DOWN", "UP", "DOWN", "UP", "DOWN", "UP", "DOWN", "UP", "DOWN" };
#define get_fwd_rule_label( ruleid ) (fwd_rule_name[(ruleid)]) 
static const char *bwd_rule_name[ 48 ] = { "LEFT", "RIGHT", "LEFT", "RIGHT", "LEFT", "RIGHT", "LEFT", "RIGHT", "LEFT", "RIGHT", "LEFT", "RIGHT", "LEFT", "RIGHT", "LEFT", "RIGHT", "LEFT", "RIGHT", "LEFT", "RIGHT", "LEFT", "RIGHT", "LEFT", "RIGHT", "UP", "DOWN", "UP", "DOWN", "UP", "DOWN", "UP", "DOWN", "UP", "DOWN", "UP", "DOWN", "UP", "DOWN", "UP", "DOWN", "UP", "DOWN", "UP", "DOWN", "UP", "DOWN", "UP", "DOWN" };
#define get_bwd_rule_label( ruleid ) (bwd_rule_name[(ruleid)]) 
#define cost_of_cheapest_fwd_rule 1
#define cost_of_costliest_fwd_rule 1
#define get_fwd_rule_cost( ruleid ) 1
#define cost_of_cheapest_bwd_rule 1
#define cost_of_costliest_bwd_rule 1
#define get_bwd_rule_cost( ruleid ) 1

static int fwd_rule_label_sets[768] = {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15};

static int bwd_rule_label_sets[768] = {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15};

static int fwd_prune_table[ 2352 ] = { 48, 96, 144, 192, 240, 288, 336, 384, 432, 480, 528, 576, 624, 672, 720, 768, 816, 864, 912, 960, 1008, 1056, 1104, 1152, 1200, 1248, 1296, 1344, 1392, 1440, 1488, 1536, 1584, 1632, 1680, 1728, 1776, 1824, 1872, 1920, 1968, 2016, 2064, 2112, 2160, 2208, 2256, 2304, 0, 0, 144, 0, 240, 288, 336, 384, 432, 480, 528, 576, 624, 672, 720, 768, 816, 864, 912, 960, 1008, 1056, 1104, 1152, 0, 1248, 1296, 0, 1392, 1440, 1488, 1536, 1584, 1632, 1680, 1728, 1776, 1824, 1872, 1920, 1968, 2016, 2064, 2112, 2160, 2208, 2256, 2304, 0, 0, 0, 192, 240, 288, 336, 384, 432, 480, 528, 576, 624, 672, 720, 768, 816, 864, 912, 960, 1008, 1056, 1104, 1152, 1200, 0, 0, 1344, 1392, 1440, 1488, 1536, 1584, 1632, 1680, 1728, 1776, 1824, 1872, 1920, 1968, 2016, 2064, 2112, 2160, 2208, 2256, 2304, 48, 0, 0, 0, 240, 0, 336, 384, 432, 480, 528, 576, 624, 672, 720, 768, 816, 864, 912, 960, 1008, 1056, 1104, 1152, 1200, 1248, 0, 1344, 1392, 0, 1488, 1536, 1584, 1632, 1680, 1728, 1776, 1824, 1872, 1920, 1968, 2016, 2064, 2112, 2160, 2208, 2256, 2304, 0, 96, 0, 0, 0, 288, 336, 384, 432, 480, 528, 576, 624, 672, 720, 768, 816, 864, 912, 960, 1008, 1056, 1104, 1152, 1200, 1248, 1296, 0, 0, 1440, 1488, 1536, 1584, 1632, 1680, 1728, 1776, 1824, 1872, 1920, 1968, 2016, 2064, 2112, 2160, 2208, 2256, 2304, 0, 0, 144, 0, 0, 0, 336, 384, 432, 480, 528, 576, 624, 672, 720, 768, 816, 864, 912, 960, 1008, 1056, 1104, 1152, 1200, 1248, 1296, 1344, 0, 1440, 1488, 0, 1584, 1632, 1680, 1728, 1776, 1824, 1872, 1920, 1968, 2016, 2064, 2112, 2160, 2208, 2256, 2304, 0, 0, 0, 192, 0, 0, 336, 384, 432, 480, 528, 576, 624, 672, 720, 768, 816, 864, 912, 960, 1008, 1056, 1104, 1152, 1200, 1248, 1296, 1344, 1392, 0, 0, 1536, 1584, 1632, 1680, 1728, 1776, 1824, 1872, 1920, 1968, 2016, 2064, 2112, 2160, 2208, 2256, 2304, 0, 0, 0, 0, 0, 0, 0, 0, 432, 0, 528, 576, 624, 672, 720, 768, 816, 864, 912, 960, 1008, 1056, 1104, 1152, 1200, 0, 0, 1344, 1392, 1440, 1488, 1536, 0, 1632, 1680, 0, 1776, 1824, 1872, 1920, 1968, 2016, 2064, 2112, 2160, 2208, 2256, 2304, 0, 0, 0, 0, 0, 0, 0, 0, 0, 480, 528, 576, 624, 672, 720, 768, 816, 864, 912, 960, 1008, 1056, 1104, 1152, 0, 1248, 1296, 0, 1392, 1440, 1488, 1536, 1584, 0, 0, 1728, 1776, 1824, 1872, 1920, 1968, 2016, 2064, 2112, 2160, 2208, 2256, 2304, 0, 0, 0, 0, 0, 0, 336, 0, 0, 0, 528, 0, 624, 672, 720, 768, 816, 864, 912, 960, 1008, 1056, 1104, 1152, 1200, 1248, 1296, 0, 0, 1440, 1488, 1536, 1584, 1632, 0, 1728, 1776, 0, 1872, 1920, 1968, 2016, 2064, 2112, 2160, 2208, 2256, 2304, 0, 0, 0, 0, 0, 0, 0, 384, 0, 0, 0, 576, 624, 672, 720, 768, 816, 864, 912, 960, 1008, 1056, 1104, 1152, 1200, 1248, 0, 1344, 1392, 0, 1488, 1536, 1584, 1632, 1680, 0, 0, 1824, 1872, 1920, 1968, 2016, 2064, 2112, 2160, 2208, 2256, 2304, 0, 0, 0, 0, 0, 0, 0, 0, 432, 0, 0, 0, 624, 672, 720, 768, 816, 864, 912, 960, 1008, 1056, 1104, 1152, 1200, 1248, 1296, 1344, 1392, 0, 0, 1536, 1584, 1632, 1680, 1728, 0, 1824, 1872, 0, 1968, 2016, 2064, 2112, 2160, 2208, 2256, 2304, 0, 0, 0, 0, 0, 0, 0, 0, 0, 480, 0, 0, 624, 672, 720, 768, 816, 864, 912, 960, 1008, 1056, 1104, 1152, 1200, 1248, 1296, 1344, 0, 1440, 1488, 0, 1584, 1632, 1680, 1728, 1776, 0, 0, 1920, 1968, 2016, 2064, 2112, 2160, 2208, 2256, 2304, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 720, 0, 816, 864, 912, 960, 1008, 1056, 1104, 1152, 1200, 1248, 1296, 1344, 1392, 1440, 1488, 1536, 1584, 0, 0, 1728, 1776, 1824, 1872, 1920, 0, 2016, 2064, 0, 2160, 2208, 2256, 2304, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 768, 816, 864, 912, 960, 1008, 1056, 1104, 1152, 1200, 1248, 1296, 1344, 1392, 1440, 1488, 1536, 0, 1632, 1680, 0, 1776, 1824, 1872, 1920, 1968, 0, 0, 2112, 2160, 2208, 2256, 2304, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 624, 0, 0, 0, 816, 0, 912, 960, 1008, 1056, 1104, 1152, 1200, 1248, 1296, 1344, 1392, 1440, 1488, 1536, 1584, 1632, 1680, 0, 0, 1824, 1872, 1920, 1968, 2016, 0, 2112, 2160, 0, 2256, 2304, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 672, 0, 0, 0, 864, 912, 960, 1008, 1056, 1104, 1152, 1200, 1248, 1296, 1344, 1392, 1440, 1488, 1536, 1584, 1632, 0, 1728, 1776, 0, 1872, 1920, 1968, 2016, 2064, 0, 0, 2208, 2256, 2304, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 720, 0, 0, 0, 912, 960, 1008, 1056, 1104, 1152, 1200, 1248, 1296, 1344, 1392, 1440, 1488, 1536, 1584, 1632, 1680, 1728, 1776, 0, 0, 1920, 1968, 2016, 2064, 2112, 0, 2208, 2256, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 768, 0, 0, 912, 960, 1008, 1056, 1104, 1152, 1200, 1248, 1296, 1344, 1392, 1440, 1488, 1536, 1584, 1632, 1680, 1728, 0, 1824, 1872, 0, 1968, 2016, 2064, 2112, 2160, 0, 0, 2304, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1008, 0, 1104, 1152, 1200, 1248, 1296, 1344, 1392, 1440, 1488, 1536, 1584, 1632, 1680, 1728, 1776, 1824, 1872, 1920, 1968, 0, 0, 2112, 2160, 2208, 2256, 2304, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1056, 1104, 1152, 1200, 1248, 1296, 1344, 1392, 1440, 1488, 1536, 1584, 1632, 1680, 1728, 1776, 1824, 1872, 1920, 0, 2016, 2064, 0, 2160, 2208, 2256, 2304, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 912, 0, 0, 0, 1104, 0, 1200, 1248, 1296, 1344, 1392, 1440, 1488, 1536, 1584, 1632, 1680, 1728, 1776, 1824, 1872, 1920, 1968, 2016, 2064, 0, 0, 2208, 2256, 2304, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 960, 0, 0, 0, 1152, 1200, 1248, 1296, 1344, 1392, 1440, 1488, 1536, 1584, 1632, 1680, 1728, 1776, 1824, 1872, 1920, 1968, 2016, 0, 2112, 2160, 0, 2256, 2304, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1008, 0, 0, 0, 1200, 1248, 1296, 1344, 1392, 1440, 1488, 1536, 1584, 1632, 1680, 1728, 1776, 1824, 1872, 1920, 1968, 2016, 2064, 2112, 2160, 0, 0, 2304, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1056, 0, 0, 1200, 1248, 1296, 1344, 1392, 1440, 1488, 1536, 1584, 1632, 1680, 1728, 1776, 1824, 1872, 1920, 1968, 2016, 2064, 2112, 0, 2208, 2256, 0, 0, 96, 0, 0, 0, 0, 336, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1296, 1344, 1392, 1440, 1488, 1536, 1584, 0, 1680, 1728, 1776, 1824, 1872, 1920, 1968, 2016, 2064, 2112, 2160, 2208, 2256, 2304, 48, 0, 0, 0, 0, 0, 0, 384, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1296, 1344, 1392, 1440, 1488, 1536, 0, 1632, 1680, 1728, 1776, 1824, 1872, 1920, 1968, 2016, 2064, 2112, 2160, 2208, 2256, 2304, 48, 0, 0, 192, 0, 0, 0, 384, 432, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1392, 1440, 1488, 1536, 1584, 1632, 1680, 0, 1776, 1824, 1872, 1920, 1968, 2016, 2064, 2112, 2160, 2208, 2256, 2304, 0, 96, 144, 0, 0, 0, 336, 0, 0, 480, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1392, 1440, 1488, 1536, 1584, 1632, 0, 1728, 1776, 1824, 1872, 1920, 1968, 2016, 2064, 2112, 2160, 2208, 2256, 2304, 0, 0, 144, 0, 0, 288, 0, 0, 0, 480, 528, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1488, 1536, 1584, 1632, 1680, 1728, 1776, 0, 1872, 1920, 1968, 2016, 2064, 2112, 2160, 2208, 2256, 2304, 0, 0, 0, 192, 240, 0, 0, 0, 432, 0, 0, 576, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1488, 1536, 1584, 1632, 1680, 1728, 0, 1824, 1872, 1920, 1968, 2016, 2064, 2112, 2160, 2208, 2256, 2304, 0, 0, 0, 0, 240, 0, 0, 0, 0, 0, 0, 576, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1584, 1632, 1680, 1728, 1776, 1824, 1872, 0, 1968, 2016, 2064, 2112, 2160, 2208, 2256, 2304, 0, 0, 0, 0, 0, 288, 0, 0, 0, 0, 528, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1584, 1632, 1680, 1728, 1776, 1824, 0, 1920, 1968, 2016, 2064, 2112, 2160, 2208, 2256, 2304, 0, 0, 0, 0, 0, 0, 0, 384, 0, 0, 0, 0, 624, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1200, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1680, 1728, 1776, 1824, 1872, 1920, 1968, 0, 2064, 2112, 2160, 2208, 2256, 2304, 0, 0, 0, 0, 0, 0, 336, 0, 0, 0, 0, 0, 0, 672, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1248, 0, 0, 0, 0, 0, 0, 0, 0, 1680, 1728, 1776, 1824, 1872, 1920, 0, 2016, 2064, 2112, 2160, 2208, 2256, 2304, 0, 0, 0, 0, 0, 0, 336, 0, 0, 480, 0, 0, 0, 672, 720, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1296, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1776, 1824, 1872, 1920, 1968, 2016, 2064, 0, 2160, 2208, 2256, 2304, 0, 0, 0, 0, 0, 0, 0, 384, 432, 0, 0, 0, 624, 0, 0, 768, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1344, 0, 0, 0, 0, 0, 0, 0, 0, 1776, 1824, 1872, 1920, 1968, 2016, 0, 2112, 2160, 2208, 2256, 2304, 0, 0, 0, 0, 0, 0, 0, 0, 432, 0, 0, 576, 0, 0, 0, 768, 816, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1392, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1872, 1920, 1968, 2016, 2064, 2112, 2160, 0, 2256, 2304, 0, 0, 0, 0, 0, 0, 0, 0, 0, 480, 528, 0, 0, 0, 720, 0, 0, 864, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1440, 0, 0, 0, 0, 0, 0, 0, 0, 1872, 1920, 1968, 2016, 2064, 2112, 0, 2208, 2256, 2304, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 528, 0, 0, 0, 0, 0, 0, 864, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1488, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1968, 2016, 2064, 2112, 2160, 2208, 2256, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 576, 0, 0, 0, 0, 816, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1536, 0, 0, 0, 0, 0, 0, 0, 0, 1968, 2016, 2064, 2112, 2160, 2208, 0, 2304, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 672, 0, 0, 0, 0, 912, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1584, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2064, 2112, 2160, 2208, 2256, 2304, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 624, 0, 0, 0, 0, 0, 0, 960, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1632, 0, 0, 0, 0, 0, 0, 0, 0, 2064, 2112, 2160, 2208, 2256, 2304, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 624, 0, 0, 768, 0, 0, 0, 960, 1008, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1680, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2160, 2208, 2256, 2304, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 672, 720, 0, 0, 0, 912, 0, 0, 1056, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1728, 0, 0, 0, 0, 0, 0, 0, 0, 2160, 2208, 2256, 2304, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 720, 0, 0, 864, 0, 0, 0, 1056, 1104, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1776, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2256, 2304, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 768, 816, 0, 0, 0, 1008, 0, 0, 1152, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1824, 0, 0, 0, 0, 0, 0, 0, 0, 2256, 2304, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 816, 0, 0, 0, 0, 0, 0, 1152, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1872, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 864, 0, 0, 0, 0, 1104, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1920, 0, 0, 0, 0, 0, 0, 0, 0 };

static void fwdrule1( const state_t *state, state_t *child_state )
{
  child_state->vars[ 0 ] = state->vars[ 1 ];
  child_state->vars[ 1 ] = 0;
  child_state->vars[ 2 ] = state->vars[ 2 ];
  child_state->vars[ 3 ] = state->vars[ 3 ];
  child_state->vars[ 4 ] = state->vars[ 4 ];
  child_state->vars[ 5 ] = state->vars[ 5 ];
  child_state->vars[ 6 ] = state->vars[ 6 ];
  child_state->vars[ 7 ] = state->vars[ 7 ];
  child_state->vars[ 8 ] = state->vars[ 8 ];
  child_state->vars[ 9 ] = state->vars[ 9 ];
  child_state->vars[ 10 ] = state->vars[ 10 ];
  child_state->vars[ 11 ] = state->vars[ 11 ];
  child_state->vars[ 12 ] = state->vars[ 12 ];
  child_state->vars[ 13 ] = state->vars[ 13 ];
  child_state->vars[ 14 ] = state->vars[ 14 ];
  child_state->vars[ 15 ] = state->vars[ 15 ];
}

static void fwdrule2( const state_t *state, state_t *child_state )
{
  child_state->vars[ 0 ] = 0;
  child_state->vars[ 1 ] = state->vars[ 0 ];
  child_state->vars[ 2 ] = state->vars[ 2 ];
  child_state->vars[ 3 ] = state->vars[ 3 ];
  child_state->vars[ 4 ] = state->vars[ 4 ];
  child_state->vars[ 5 ] = state->vars[ 5 ];
  child_state->vars[ 6 ] = state->vars[ 6 ];
  child_state->vars[ 7 ] = state->vars[ 7 ];
  child_state->vars[ 8 ] = state->vars[ 8 ];
  child_state->vars[ 9 ] = state->vars[ 9 ];
  child_state->vars[ 10 ] = state->vars[ 10 ];
  child_state->vars[ 11 ] = state->vars[ 11 ];
  child_state->vars[ 12 ] = state->vars[ 12 ];
  child_state->vars[ 13 ] = state->vars[ 13 ];
  child_state->vars[ 14 ] = state->vars[ 14 ];
  child_state->vars[ 15 ] = state->vars[ 15 ];
}

static void fwdrule3( const state_t *state, state_t *child_state )
{
  child_state->vars[ 0 ] = state->vars[ 0 ];
  child_state->vars[ 1 ] = state->vars[ 2 ];
  child_state->vars[ 2 ] = 0;
  child_state->vars[ 3 ] = state->vars[ 3 ];
  child_state->vars[ 4 ] = state->vars[ 4 ];
  child_state->vars[ 5 ] = state->vars[ 5 ];
  child_state->vars[ 6 ] = state->vars[ 6 ];
  child_state->vars[ 7 ] = state->vars[ 7 ];
  child_state->vars[ 8 ] = state->vars[ 8 ];
  child_state->vars[ 9 ] = state->vars[ 9 ];
  child_state->vars[ 10 ] = state->vars[ 10 ];
  child_state->vars[ 11 ] = state->vars[ 11 ];
  child_state->vars[ 12 ] = state->vars[ 12 ];
  child_state->vars[ 13 ] = state->vars[ 13 ];
  child_state->vars[ 14 ] = state->vars[ 14 ];
  child_state->vars[ 15 ] = state->vars[ 15 ];
}

static void fwdrule4( const state_t *state, state_t *child_state )
{
  child_state->vars[ 0 ] = state->vars[ 0 ];
  child_state->vars[ 1 ] = 0;
  child_state->vars[ 2 ] = state->vars[ 1 ];
  child_state->vars[ 3 ] = state->vars[ 3 ];
  child_state->vars[ 4 ] = state->vars[ 4 ];
  child_state->vars[ 5 ] = state->vars[ 5 ];
  child_state->vars[ 6 ] = state->vars[ 6 ];
  child_state->vars[ 7 ] = state->vars[ 7 ];
  child_state->vars[ 8 ] = state->vars[ 8 ];
  child_state->vars[ 9 ] = state->vars[ 9 ];
  child_state->vars[ 10 ] = state->vars[ 10 ];
  child_state->vars[ 11 ] = state->vars[ 11 ];
  child_state->vars[ 12 ] = state->vars[ 12 ];
  child_state->vars[ 13 ] = state->vars[ 13 ];
  child_state->vars[ 14 ] = state->vars[ 14 ];
  child_state->vars[ 15 ] = state->vars[ 15 ];
}

static void fwdrule5( const state_t *state, state_t *child_state )
{
  child_state->vars[ 0 ] = state->vars[ 0 ];
  child_state->vars[ 1 ] = state->vars[ 1 ];
  child_state->vars[ 2 ] = state->vars[ 3 ];
  child_state->vars[ 3 ] = 0;
  child_state->vars[ 4 ] = state->vars[ 4 ];
  child_state->vars[ 5 ] = state->vars[ 5 ];
  child_state->vars[ 6 ] = state->vars[ 6 ];
  child_state->vars[ 7 ] = state->vars[ 7 ];
  child_state->vars[ 8 ] = state->vars[ 8 ];
  child_state->vars[ 9 ] = state->vars[ 9 ];
  child_state->vars[ 10 ] = state->vars[ 10 ];
  child_state->vars[ 11 ] = state->vars[ 11 ];
  child_state->vars[ 12 ] = state->vars[ 12 ];
  child_state->vars[ 13 ] = state->vars[ 13 ];
  child_state->vars[ 14 ] = state->vars[ 14 ];
  child_state->vars[ 15 ] = state->vars[ 15 ];
}

static void fwdrule6( const state_t *state, state_t *child_state )
{
  child_state->vars[ 0 ] = state->vars[ 0 ];
  child_state->vars[ 1 ] = state->vars[ 1 ];
  child_state->vars[ 2 ] = 0;
  child_state->vars[ 3 ] = state->vars[ 2 ];
  child_state->vars[ 4 ] = state->vars[ 4 ];
  child_state->vars[ 5 ] = state->vars[ 5 ];
  child_state->vars[ 6 ] = state->vars[ 6 ];
  child_state->vars[ 7 ] = state->vars[ 7 ];
  child_state->vars[ 8 ] = state->vars[ 8 ];
  child_state->vars[ 9 ] = state->vars[ 9 ];
  child_state->vars[ 10 ] = state->vars[ 10 ];
  child_state->vars[ 11 ] = state->vars[ 11 ];
  child_state->vars[ 12 ] = state->vars[ 12 ];
  child_state->vars[ 13 ] = state->vars[ 13 ];
  child_state->vars[ 14 ] = state->vars[ 14 ];
  child_state->vars[ 15 ] = state->vars[ 15 ];
}

static void fwdrule7( const state_t *state, state_t *child_state )
{
  child_state->vars[ 0 ] = state->vars[ 0 ];
  child_state->vars[ 1 ] = state->vars[ 1 ];
  child_state->vars[ 2 ] = state->vars[ 2 ];
  child_state->vars[ 3 ] = state->vars[ 3 ];
  child_state->vars[ 4 ] = state->vars[ 5 ];
  child_state->vars[ 5 ] = 0;
  child_state->vars[ 6 ] = state->vars[ 6 ];
  child_state->vars[ 7 ] = state->vars[ 7 ];
  child_state->vars[ 8 ] = state->vars[ 8 ];
  child_state->vars[ 9 ] = state->vars[ 9 ];
  child_state->vars[ 10 ] = state->vars[ 10 ];
  child_state->vars[ 11 ] = state->vars[ 11 ];
  child_state->vars[ 12 ] = state->vars[ 12 ];
  child_state->vars[ 13 ] = state->vars[ 13 ];
  child_state->vars[ 14 ] = state->vars[ 14 ];
  child_state->vars[ 15 ] = state->vars[ 15 ];
}

static void fwdrule8( const state_t *state, state_t *child_state )
{
  child_state->vars[ 0 ] = state->vars[ 0 ];
  child_state->vars[ 1 ] = state->vars[ 1 ];
  child_state->vars[ 2 ] = state->vars[ 2 ];
  child_state->vars[ 3 ] = state->vars[ 3 ];
  child_state->vars[ 4 ] = 0;
  child_state->vars[ 5 ] = state->vars[ 4 ];
  child_state->vars[ 6 ] = state->vars[ 6 ];
  child_state->vars[ 7 ] = state->vars[ 7 ];
  child_state->vars[ 8 ] = state->vars[ 8 ];
  child_state->vars[ 9 ] = state->vars[ 9 ];
  child_state->vars[ 10 ] = state->vars[ 10 ];
  child_state->vars[ 11 ] = state->vars[ 11 ];
  child_state->vars[ 12 ] = state->vars[ 12 ];
  child_state->vars[ 13 ] = state->vars[ 13 ];
  child_state->vars[ 14 ] = state->vars[ 14 ];
  child_state->vars[ 15 ] = state->vars[ 15 ];
}

static void fwdrule9( const state_t *state, state_t *child_state )
{
  child_state->vars[ 0 ] = state->vars[ 0 ];
  child_state->vars[ 1 ] = state->vars[ 1 ];
  child_state->vars[ 2 ] = state->vars[ 2 ];
  child_state->vars[ 3 ] = state->vars[ 3 ];
  child_state->vars[ 4 ] = state->vars[ 4 ];
  child_state->vars[ 5 ] = state->vars[ 6 ];
  child_state->vars[ 6 ] = 0;
  child_state->vars[ 7 ] = state->vars[ 7 ];
  child_state->vars[ 8 ] = state->vars[ 8 ];
  child_state->vars[ 9 ] = state->vars[ 9 ];
  child_state->vars[ 10 ] = state->vars[ 10 ];
  child_state->vars[ 11 ] = state->vars[ 11 ];
  child_state->vars[ 12 ] = state->vars[ 12 ];
  child_state->vars[ 13 ] = state->vars[ 13 ];
  child_state->vars[ 14 ] = state->vars[ 14 ];
  child_state->vars[ 15 ] = state->vars[ 15 ];
}

static void fwdrule10( const state_t *state, state_t *child_state )
{
  child_state->vars[ 0 ] = state->vars[ 0 ];
  child_state->vars[ 1 ] = state->vars[ 1 ];
  child_state->vars[ 2 ] = state->vars[ 2 ];
  child_state->vars[ 3 ] = state->vars[ 3 ];
  child_state->vars[ 4 ] = state->vars[ 4 ];
  child_state->vars[ 5 ] = 0;
  child_state->vars[ 6 ] = state->vars[ 5 ];
  child_state->vars[ 7 ] = state->vars[ 7 ];
  child_state->vars[ 8 ] = state->vars[ 8 ];
  child_state->vars[ 9 ] = state->vars[ 9 ];
  child_state->vars[ 10 ] = state->vars[ 10 ];
  child_state->vars[ 11 ] = state->vars[ 11 ];
  child_state->vars[ 12 ] = state->vars[ 12 ];
  child_state->vars[ 13 ] = state->vars[ 13 ];
  child_state->vars[ 14 ] = state->vars[ 14 ];
  child_state->vars[ 15 ] = state->vars[ 15 ];
}

static void fwdrule11( const state_t *state, state_t *child_state )
{
  child_state->vars[ 0 ] = state->vars[ 0 ];
  child_state->vars[ 1 ] = state->vars[ 1 ];
  child_state->vars[ 2 ] = state->vars[ 2 ];
  child_state->vars[ 3 ] = state->vars[ 3 ];
  child_state->vars[ 4 ] = state->vars[ 4 ];
  child_state->vars[ 5 ] = state->vars[ 5 ];
  child_state->vars[ 6 ] = state->vars[ 7 ];
  child_state->vars[ 7 ] = 0;
  child_state->vars[ 8 ] = state->vars[ 8 ];
  child_state->vars[ 9 ] = state->vars[ 9 ];
  child_state->vars[ 10 ] = state->vars[ 10 ];
  child_state->vars[ 11 ] = state->vars[ 11 ];
  child_state->vars[ 12 ] = state->vars[ 12 ];
  child_state->vars[ 13 ] = state->vars[ 13 ];
  child_state->vars[ 14 ] = state->vars[ 14 ];
  child_state->vars[ 15 ] = state->vars[ 15 ];
}

static void fwdrule12( const state_t *state, state_t *child_state )
{
  child_state->vars[ 0 ] = state->vars[ 0 ];
  child_state->vars[ 1 ] = state->vars[ 1 ];
  child_state->vars[ 2 ] = state->vars[ 2 ];
  child_state->vars[ 3 ] = state->vars[ 3 ];
  child_state->vars[ 4 ] = state->vars[ 4 ];
  child_state->vars[ 5 ] = state->vars[ 5 ];
  child_state->vars[ 6 ] = 0;
  child_state->vars[ 7 ] = state->vars[ 6 ];
  child_state->vars[ 8 ] = state->vars[ 8 ];
  child_state->vars[ 9 ] = state->vars[ 9 ];
  child_state->vars[ 10 ] = state->vars[ 10 ];
  child_state->vars[ 11 ] = state->vars[ 11 ];
  child_state->vars[ 12 ] = state->vars[ 12 ];
  child_state->vars[ 13 ] = state->vars[ 13 ];
  child_state->vars[ 14 ] = state->vars[ 14 ];
  child_state->vars[ 15 ] = state->vars[ 15 ];
}

static void fwdrule13( const state_t *state, state_t *child_state )
{
  child_state->vars[ 0 ] = state->vars[ 0 ];
  child_state->vars[ 1 ] = state->vars[ 1 ];
  child_state->vars[ 2 ] = state->vars[ 2 ];
  child_state->vars[ 3 ] = state->vars[ 3 ];
  child_state->vars[ 4 ] = state->vars[ 4 ];
  child_state->vars[ 5 ] = state->vars[ 5 ];
  child_state->vars[ 6 ] = state->vars[ 6 ];
  child_state->vars[ 7 ] = state->vars[ 7 ];
  child_state->vars[ 8 ] = state->vars[ 9 ];
  child_state->vars[ 9 ] = 0;
  child_state->vars[ 10 ] = state->vars[ 10 ];
  child_state->vars[ 11 ] = state->vars[ 11 ];
  child_state->vars[ 12 ] = state->vars[ 12 ];
  child_state->vars[ 13 ] = state->vars[ 13 ];
  child_state->vars[ 14 ] = state->vars[ 14 ];
  child_state->vars[ 15 ] = state->vars[ 15 ];
}

static void fwdrule14( const state_t *state, state_t *child_state )
{
  child_state->vars[ 0 ] = state->vars[ 0 ];
  child_state->vars[ 1 ] = state->vars[ 1 ];
  child_state->vars[ 2 ] = state->vars[ 2 ];
  child_state->vars[ 3 ] = state->vars[ 3 ];
  child_state->vars[ 4 ] = state->vars[ 4 ];
  child_state->vars[ 5 ] = state->vars[ 5 ];
  child_state->vars[ 6 ] = state->vars[ 6 ];
  child_state->vars[ 7 ] = state->vars[ 7 ];
  child_state->vars[ 8 ] = 0;
  child_state->vars[ 9 ] = state->vars[ 8 ];
  child_state->vars[ 10 ] = state->vars[ 10 ];
  child_state->vars[ 11 ] = state->vars[ 11 ];
  child_state->vars[ 12 ] = state->vars[ 12 ];
  child_state->vars[ 13 ] = state->vars[ 13 ];
  child_state->vars[ 14 ] = state->vars[ 14 ];
  child_state->vars[ 15 ] = state->vars[ 15 ];
}

static void fwdrule15( const state_t *state, state_t *child_state )
{
  child_state->vars[ 0 ] = state->vars[ 0 ];
  child_state->vars[ 1 ] = state->vars[ 1 ];
  child_state->vars[ 2 ] = state->vars[ 2 ];
  child_state->vars[ 3 ] = state->vars[ 3 ];
  child_state->vars[ 4 ] = state->vars[ 4 ];
  child_state->vars[ 5 ] = state->vars[ 5 ];
  child_state->vars[ 6 ] = state->vars[ 6 ];
  child_state->vars[ 7 ] = state->vars[ 7 ];
  child_state->vars[ 8 ] = state->vars[ 8 ];
  child_state->vars[ 9 ] = state->vars[ 10 ];
  child_state->vars[ 10 ] = 0;
  child_state->vars[ 11 ] = state->vars[ 11 ];
  child_state->vars[ 12 ] = state->vars[ 12 ];
  child_state->vars[ 13 ] = state->vars[ 13 ];
  child_state->vars[ 14 ] = state->vars[ 14 ];
  child_state->vars[ 15 ] = state->vars[ 15 ];
}

static void fwdrule16( const state_t *state, state_t *child_state )
{
  child_state->vars[ 0 ] = state->vars[ 0 ];
  child_state->vars[ 1 ] = state->vars[ 1 ];
  child_state->vars[ 2 ] = state->vars[ 2 ];
  child_state->vars[ 3 ] = state->vars[ 3 ];
  child_state->vars[ 4 ] = state->vars[ 4 ];
  child_state->vars[ 5 ] = state->vars[ 5 ];
  child_state->vars[ 6 ] = state->vars[ 6 ];
  child_state->vars[ 7 ] = state->vars[ 7 ];
  child_state->vars[ 8 ] = state->vars[ 8 ];
  child_state->vars[ 9 ] = 0;
  child_state->vars[ 10 ] = state->vars[ 9 ];
  child_state->vars[ 11 ] = state->vars[ 11 ];
  child_state->vars[ 12 ] = state->vars[ 12 ];
  child_state->vars[ 13 ] = state->vars[ 13 ];
  child_state->vars[ 14 ] = state->vars[ 14 ];
  child_state->vars[ 15 ] = state->vars[ 15 ];
}

static void fwdrule17( const state_t *state, state_t *child_state )
{
  child_state->vars[ 0 ] = state->vars[ 0 ];
  child_state->vars[ 1 ] = state->vars[ 1 ];
  child_state->vars[ 2 ] = state->vars[ 2 ];
  child_state->vars[ 3 ] = state->vars[ 3 ];
  child_state->vars[ 4 ] = state->vars[ 4 ];
  child_state->vars[ 5 ] = state->vars[ 5 ];
  child_state->vars[ 6 ] = state->vars[ 6 ];
  child_state->vars[ 7 ] = state->vars[ 7 ];
  child_state->vars[ 8 ] = state->vars[ 8 ];
  child_state->vars[ 9 ] = state->vars[ 9 ];
  child_state->vars[ 10 ] = state->vars[ 11 ];
  child_state->vars[ 11 ] = 0;
  child_state->vars[ 12 ] = state->vars[ 12 ];
  child_state->vars[ 13 ] = state->vars[ 13 ];
  child_state->vars[ 14 ] = state->vars[ 14 ];
  child_state->vars[ 15 ] = state->vars[ 15 ];
}

static void fwdrule18( const state_t *state, state_t *child_state )
{
  child_state->vars[ 0 ] = state->vars[ 0 ];
  child_state->vars[ 1 ] = state->vars[ 1 ];
  child_state->vars[ 2 ] = state->vars[ 2 ];
  child_state->vars[ 3 ] = state->vars[ 3 ];
  child_state->vars[ 4 ] = state->vars[ 4 ];
  child_state->vars[ 5 ] = state->vars[ 5 ];
  child_state->vars[ 6 ] = state->vars[ 6 ];
  child_state->vars[ 7 ] = state->vars[ 7 ];
  child_state->vars[ 8 ] = state->vars[ 8 ];
  child_state->vars[ 9 ] = state->vars[ 9 ];
  child_state->vars[ 10 ] = 0;
  child_state->vars[ 11 ] = state->vars[ 10 ];
  child_state->vars[ 12 ] = state->vars[ 12 ];
  child_state->vars[ 13 ] = state->vars[ 13 ];
  child_state->vars[ 14 ] = state->vars[ 14 ];
  child_state->vars[ 15 ] = state->vars[ 15 ];
}

static void fwdrule19( const state_t *state, state_t *child_state )
{
  child_state->vars[ 0 ] = state->vars[ 0 ];
  child_state->vars[ 1 ] = state->vars[ 1 ];
  child_state->vars[ 2 ] = state->vars[ 2 ];
  child_state->vars[ 3 ] = state->vars[ 3 ];
  child_state->vars[ 4 ] = state->vars[ 4 ];
  child_state->vars[ 5 ] = state->vars[ 5 ];
  child_state->vars[ 6 ] = state->vars[ 6 ];
  child_state->vars[ 7 ] = state->vars[ 7 ];
  child_state->vars[ 8 ] = state->vars[ 8 ];
  child_state->vars[ 9 ] = state->vars[ 9 ];
  child_state->vars[ 10 ] = state->vars[ 10 ];
  child_state->vars[ 11 ] = state->vars[ 11 ];
  child_state->vars[ 12 ] = state->vars[ 13 ];
  child_state->vars[ 13 ] = 0;
  child_state->vars[ 14 ] = state->vars[ 14 ];
  child_state->vars[ 15 ] = state->vars[ 15 ];
}

static void fwdrule20( const state_t *state, state_t *child_state )
{
  child_state->vars[ 0 ] = state->vars[ 0 ];
  child_state->vars[ 1 ] = state->vars[ 1 ];
  child_state->vars[ 2 ] = state->vars[ 2 ];
  child_state->vars[ 3 ] = state->vars[ 3 ];
  child_state->vars[ 4 ] = state->vars[ 4 ];
  child_state->vars[ 5 ] = state->vars[ 5 ];
  child_state->vars[ 6 ] = state->vars[ 6 ];
  child_state->vars[ 7 ] = state->vars[ 7 ];
  child_state->vars[ 8 ] = state->vars[ 8 ];
  child_state->vars[ 9 ] = state->vars[ 9 ];
  child_state->vars[ 10 ] = state->vars[ 10 ];
  child_state->vars[ 11 ] = state->vars[ 11 ];
  child_state->vars[ 12 ] = 0;
  child_state->vars[ 13 ] = state->vars[ 12 ];
  child_state->vars[ 14 ] = state->vars[ 14 ];
  child_state->vars[ 15 ] = state->vars[ 15 ];
}

static void fwdrule21( const state_t *state, state_t *child_state )
{
  child_state->vars[ 0 ] = state->vars[ 0 ];
  child_state->vars[ 1 ] = state->vars[ 1 ];
  child_state->vars[ 2 ] = state->vars[ 2 ];
  child_state->vars[ 3 ] = state->vars[ 3 ];
  child_state->vars[ 4 ] = state->vars[ 4 ];
  child_state->vars[ 5 ] = state->vars[ 5 ];
  child_state->vars[ 6 ] = state->vars[ 6 ];
  child_state->vars[ 7 ] = state->vars[ 7 ];
  child_state->vars[ 8 ] = state->vars[ 8 ];
  child_state->vars[ 9 ] = state->vars[ 9 ];
  child_state->vars[ 10 ] = state->vars[ 10 ];
  child_state->vars[ 11 ] = state->vars[ 11 ];
  child_state->vars[ 12 ] = state->vars[ 12 ];
  child_state->vars[ 13 ] = state->vars[ 14 ];
  child_state->vars[ 14 ] = 0;
  child_state->vars[ 15 ] = state->vars[ 15 ];
}

static void fwdrule22( const state_t *state, state_t *child_state )
{
  child_state->vars[ 0 ] = state->vars[ 0 ];
  child_state->vars[ 1 ] = state->vars[ 1 ];
  child_state->vars[ 2 ] = state->vars[ 2 ];
  child_state->vars[ 3 ] = state->vars[ 3 ];
  child_state->vars[ 4 ] = state->vars[ 4 ];
  child_state->vars[ 5 ] = state->vars[ 5 ];
  child_state->vars[ 6 ] = state->vars[ 6 ];
  child_state->vars[ 7 ] = state->vars[ 7 ];
  child_state->vars[ 8 ] = state->vars[ 8 ];
  child_state->vars[ 9 ] = state->vars[ 9 ];
  child_state->vars[ 10 ] = state->vars[ 10 ];
  child_state->vars[ 11 ] = state->vars[ 11 ];
  child_state->vars[ 12 ] = state->vars[ 12 ];
  child_state->vars[ 13 ] = 0;
  child_state->vars[ 14 ] = state->vars[ 13 ];
  child_state->vars[ 15 ] = state->vars[ 15 ];
}

static void fwdrule23( const state_t *state, state_t *child_state )
{
  child_state->vars[ 0 ] = state->vars[ 0 ];
  child_state->vars[ 1 ] = state->vars[ 1 ];
  child_state->vars[ 2 ] = state->vars[ 2 ];
  child_state->vars[ 3 ] = state->vars[ 3 ];
  child_state->vars[ 4 ] = state->vars[ 4 ];
  child_state->vars[ 5 ] = state->vars[ 5 ];
  child_state->vars[ 6 ] = state->vars[ 6 ];
  child_state->vars[ 7 ] = state->vars[ 7 ];
  child_state->vars[ 8 ] = state->vars[ 8 ];
  child_state->vars[ 9 ] = state->vars[ 9 ];
  child_state->vars[ 10 ] = state->vars[ 10 ];
  child_state->vars[ 11 ] = state->vars[ 11 ];
  child_state->vars[ 12 ] = state->vars[ 12 ];
  child_state->vars[ 13 ] = state->vars[ 13 ];
  child_state->vars[ 14 ] = state->vars[ 15 ];
  child_state->vars[ 15 ] = 0;
}

static void fwdrule24( const state_t *state, state_t *child_state )
{
  child_state->vars[ 0 ] = state->vars[ 0 ];
  child_state->vars[ 1 ] = state->vars[ 1 ];
  child_state->vars[ 2 ] = state->vars[ 2 ];
  child_state->vars[ 3 ] = state->vars[ 3 ];
  child_state->vars[ 4 ] = state->vars[ 4 ];
  child_state->vars[ 5 ] = state->vars[ 5 ];
  child_state->vars[ 6 ] = state->vars[ 6 ];
  child_state->vars[ 7 ] = state->vars[ 7 ];
  child_state->vars[ 8 ] = state->vars[ 8 ];
  child_state->vars[ 9 ] = state->vars[ 9 ];
  child_state->vars[ 10 ] = state->vars[ 10 ];
  child_state->vars[ 11 ] = state->vars[ 11 ];
  child_state->vars[ 12 ] = state->vars[ 12 ];
  child_state->vars[ 13 ] = state->vars[ 13 ];
  child_state->vars[ 14 ] = 0;
  child_state->vars[ 15 ] = state->vars[ 14 ];
}

static void fwdrule25( const state_t *state, state_t *child_state )
{
  child_state->vars[ 0 ] = state->vars[ 4 ];
  child_state->vars[ 1 ] = state->vars[ 1 ];
  child_state->vars[ 2 ] = state->vars[ 2 ];
  child_state->vars[ 3 ] = state->vars[ 3 ];
  child_state->vars[ 4 ] = 0;
  child_state->vars[ 5 ] = state->vars[ 5 ];
  child_state->vars[ 6 ] = state->vars[ 6 ];
  child_state->vars[ 7 ] = state->vars[ 7 ];
  child_state->vars[ 8 ] = state->vars[ 8 ];
  child_state->vars[ 9 ] = state->vars[ 9 ];
  child_state->vars[ 10 ] = state->vars[ 10 ];
  child_state->vars[ 11 ] = state->vars[ 11 ];
  child_state->vars[ 12 ] = state->vars[ 12 ];
  child_state->vars[ 13 ] = state->vars[ 13 ];
  child_state->vars[ 14 ] = state->vars[ 14 ];
  child_state->vars[ 15 ] = state->vars[ 15 ];
}

static void fwdrule26( const state_t *state, state_t *child_state )
{
  child_state->vars[ 0 ] = 0;
  child_state->vars[ 1 ] = state->vars[ 1 ];
  child_state->vars[ 2 ] = state->vars[ 2 ];
  child_state->vars[ 3 ] = state->vars[ 3 ];
  child_state->vars[ 4 ] = state->vars[ 0 ];
  child_state->vars[ 5 ] = state->vars[ 5 ];
  child_state->vars[ 6 ] = state->vars[ 6 ];
  child_state->vars[ 7 ] = state->vars[ 7 ];
  child_state->vars[ 8 ] = state->vars[ 8 ];
  child_state->vars[ 9 ] = state->vars[ 9 ];
  child_state->vars[ 10 ] = state->vars[ 10 ];
  child_state->vars[ 11 ] = state->vars[ 11 ];
  child_state->vars[ 12 ] = state->vars[ 12 ];
  child_state->vars[ 13 ] = state->vars[ 13 ];
  child_state->vars[ 14 ] = state->vars[ 14 ];
  child_state->vars[ 15 ] = state->vars[ 15 ];
}

static void fwdrule27( const state_t *state, state_t *child_state )
{
  child_state->vars[ 0 ] = state->vars[ 0 ];
  child_state->vars[ 1 ] = state->vars[ 5 ];
  child_state->vars[ 2 ] = state->vars[ 2 ];
  child_state->vars[ 3 ] = state->vars[ 3 ];
  child_state->vars[ 4 ] = state->vars[ 4 ];
  child_state->vars[ 5 ] = 0;
  child_state->vars[ 6 ] = state->vars[ 6 ];
  child_state->vars[ 7 ] = state->vars[ 7 ];
  child_state->vars[ 8 ] = state->vars[ 8 ];
  child_state->vars[ 9 ] = state->vars[ 9 ];
  child_state->vars[ 10 ] = state->vars[ 10 ];
  child_state->vars[ 11 ] = state->vars[ 11 ];
  child_state->vars[ 12 ] = state->vars[ 12 ];
  child_state->vars[ 13 ] = state->vars[ 13 ];
  child_state->vars[ 14 ] = state->vars[ 14 ];
  child_state->vars[ 15 ] = state->vars[ 15 ];
}

static void fwdrule28( const state_t *state, state_t *child_state )
{
  child_state->vars[ 0 ] = state->vars[ 0 ];
  child_state->vars[ 1 ] = 0;
  child_state->vars[ 2 ] = state->vars[ 2 ];
  child_state->vars[ 3 ] = state->vars[ 3 ];
  child_state->vars[ 4 ] = state->vars[ 4 ];
  child_state->vars[ 5 ] = state->vars[ 1 ];
  child_state->vars[ 6 ] = state->vars[ 6 ];
  child_state->vars[ 7 ] = state->vars[ 7 ];
  child_state->vars[ 8 ] = state->vars[ 8 ];
  child_state->vars[ 9 ] = state->vars[ 9 ];
  child_state->vars[ 10 ] = state->vars[ 10 ];
  child_state->vars[ 11 ] = state->vars[ 11 ];
  child_state->vars[ 12 ] = state->vars[ 12 ];
  child_state->vars[ 13 ] = state->vars[ 13 ];
  child_state->vars[ 14 ] = state->vars[ 14 ];
  child_state->vars[ 15 ] = state->vars[ 15 ];
}

static void fwdrule29( const state_t *state, state_t *child_state )
{
  child_state->vars[ 0 ] = state->vars[ 0 ];
  child_state->vars[ 1 ] = state->vars[ 1 ];
  child_state->vars[ 2 ] = state->vars[ 6 ];
  child_state->vars[ 3 ] = state->vars[ 3 ];
  child_state->vars[ 4 ] = state->vars[ 4 ];
  child_state->vars[ 5 ] = state->vars[ 5 ];
  child_state->vars[ 6 ] = 0;
  child_state->vars[ 7 ] = state->vars[ 7 ];
  child_state->vars[ 8 ] = state->vars[ 8 ];
  child_state->vars[ 9 ] = state->vars[ 9 ];
  child_state->vars[ 10 ] = state->vars[ 10 ];
  child_state->vars[ 11 ] = state->vars[ 11 ];
  child_state->vars[ 12 ] = state->vars[ 12 ];
  child_state->vars[ 13 ] = state->vars[ 13 ];
  child_state->vars[ 14 ] = state->vars[ 14 ];
  child_state->vars[ 15 ] = state->vars[ 15 ];
}

static void fwdrule30( const state_t *state, state_t *child_state )
{
  child_state->vars[ 0 ] = state->vars[ 0 ];
  child_state->vars[ 1 ] = state->vars[ 1 ];
  child_state->vars[ 2 ] = 0;
  child_state->vars[ 3 ] = state->vars[ 3 ];
  child_state->vars[ 4 ] = state->vars[ 4 ];
  child_state->vars[ 5 ] = state->vars[ 5 ];
  child_state->vars[ 6 ] = state->vars[ 2 ];
  child_state->vars[ 7 ] = state->vars[ 7 ];
  child_state->vars[ 8 ] = state->vars[ 8 ];
  child_state->vars[ 9 ] = state->vars[ 9 ];
  child_state->vars[ 10 ] = state->vars[ 10 ];
  child_state->vars[ 11 ] = state->vars[ 11 ];
  child_state->vars[ 12 ] = state->vars[ 12 ];
  child_state->vars[ 13 ] = state->vars[ 13 ];
  child_state->vars[ 14 ] = state->vars[ 14 ];
  child_state->vars[ 15 ] = state->vars[ 15 ];
}

static void fwdrule31( const state_t *state, state_t *child_state )
{
  child_state->vars[ 0 ] = state->vars[ 0 ];
  child_state->vars[ 1 ] = state->vars[ 1 ];
  child_state->vars[ 2 ] = state->vars[ 2 ];
  child_state->vars[ 3 ] = state->vars[ 7 ];
  child_state->vars[ 4 ] = state->vars[ 4 ];
  child_state->vars[ 5 ] = state->vars[ 5 ];
  child_state->vars[ 6 ] = state->vars[ 6 ];
  child_state->vars[ 7 ] = 0;
  child_state->vars[ 8 ] = state->vars[ 8 ];
  child_state->vars[ 9 ] = state->vars[ 9 ];
  child_state->vars[ 10 ] = state->vars[ 10 ];
  child_state->vars[ 11 ] = state->vars[ 11 ];
  child_state->vars[ 12 ] = state->vars[ 12 ];
  child_state->vars[ 13 ] = state->vars[ 13 ];
  child_state->vars[ 14 ] = state->vars[ 14 ];
  child_state->vars[ 15 ] = state->vars[ 15 ];
}

static void fwdrule32( const state_t *state, state_t *child_state )
{
  child_state->vars[ 0 ] = state->vars[ 0 ];
  child_state->vars[ 1 ] = state->vars[ 1 ];
  child_state->vars[ 2 ] = state->vars[ 2 ];
  child_state->vars[ 3 ] = 0;
  child_state->vars[ 4 ] = state->vars[ 4 ];
  child_state->vars[ 5 ] = state->vars[ 5 ];
  child_state->vars[ 6 ] = state->vars[ 6 ];
  child_state->vars[ 7 ] = state->vars[ 3 ];
  child_state->vars[ 8 ] = state->vars[ 8 ];
  child_state->vars[ 9 ] = state->vars[ 9 ];
  child_state->vars[ 10 ] = state->vars[ 10 ];
  child_state->vars[ 11 ] = state->vars[ 11 ];
  child_state->vars[ 12 ] = state->vars[ 12 ];
  child_state->vars[ 13 ] = state->vars[ 13 ];
  child_state->vars[ 14 ] = state->vars[ 14 ];
  child_state->vars[ 15 ] = state->vars[ 15 ];
}

static void fwdrule33( const state_t *state, state_t *child_state )
{
  child_state->vars[ 0 ] = state->vars[ 0 ];
  child_state->vars[ 1 ] = state->vars[ 1 ];
  child_state->vars[ 2 ] = state->vars[ 2 ];
  child_state->vars[ 3 ] = state->vars[ 3 ];
  child_state->vars[ 4 ] = state->vars[ 8 ];
  child_state->vars[ 5 ] = state->vars[ 5 ];
  child_state->vars[ 6 ] = state->vars[ 6 ];
  child_state->vars[ 7 ] = state->vars[ 7 ];
  child_state->vars[ 8 ] = 0;
  child_state->vars[ 9 ] = state->vars[ 9 ];
  child_state->vars[ 10 ] = state->vars[ 10 ];
  child_state->vars[ 11 ] = state->vars[ 11 ];
  child_state->vars[ 12 ] = state->vars[ 12 ];
  child_state->vars[ 13 ] = state->vars[ 13 ];
  child_state->vars[ 14 ] = state->vars[ 14 ];
  child_state->vars[ 15 ] = state->vars[ 15 ];
}

static void fwdrule34( const state_t *state, state_t *child_state )
{
  child_state->vars[ 0 ] = state->vars[ 0 ];
  child_state->vars[ 1 ] = state->vars[ 1 ];
  child_state->vars[ 2 ] = state->vars[ 2 ];
  child_state->vars[ 3 ] = state->vars[ 3 ];
  child_state->vars[ 4 ] = 0;
  child_state->vars[ 5 ] = state->vars[ 5 ];
  child_state->vars[ 6 ] = state->vars[ 6 ];
  child_state->vars[ 7 ] = state->vars[ 7 ];
  child_state->vars[ 8 ] = state->vars[ 4 ];
  child_state->vars[ 9 ] = state->vars[ 9 ];
  child_state->vars[ 10 ] = state->vars[ 10 ];
  child_state->vars[ 11 ] = state->vars[ 11 ];
  child_state->vars[ 12 ] = state->vars[ 12 ];
  child_state->vars[ 13 ] = state->vars[ 13 ];
  child_state->vars[ 14 ] = state->vars[ 14 ];
  child_state->vars[ 15 ] = state->vars[ 15 ];
}

static void fwdrule35( const state_t *state, state_t *child_state )
{
  child_state->vars[ 0 ] = state->vars[ 0 ];
  child_state->vars[ 1 ] = state->vars[ 1 ];
  child_state->vars[ 2 ] = state->vars[ 2 ];
  child_state->vars[ 3 ] = state->vars[ 3 ];
  child_state->vars[ 4 ] = state->vars[ 4 ];
  child_state->vars[ 5 ] = state->vars[ 9 ];
  child_state->vars[ 6 ] = state->vars[ 6 ];
  child_state->vars[ 7 ] = state->vars[ 7 ];
  child_state->vars[ 8 ] = state->vars[ 8 ];
  child_state->vars[ 9 ] = 0;
  child_state->vars[ 10 ] = state->vars[ 10 ];
  child_state->vars[ 11 ] = state->vars[ 11 ];
  child_state->vars[ 12 ] = state->vars[ 12 ];
  child_state->vars[ 13 ] = state->vars[ 13 ];
  child_state->vars[ 14 ] = state->vars[ 14 ];
  child_state->vars[ 15 ] = state->vars[ 15 ];
}

static void fwdrule36( const state_t *state, state_t *child_state )
{
  child_state->vars[ 0 ] = state->vars[ 0 ];
  child_state->vars[ 1 ] = state->vars[ 1 ];
  child_state->vars[ 2 ] = state->vars[ 2 ];
  child_state->vars[ 3 ] = state->vars[ 3 ];
  child_state->vars[ 4 ] = state->vars[ 4 ];
  child_state->vars[ 5 ] = 0;
  child_state->vars[ 6 ] = state->vars[ 6 ];
  child_state->vars[ 7 ] = state->vars[ 7 ];
  child_state->vars[ 8 ] = state->vars[ 8 ];
  child_state->vars[ 9 ] = state->vars[ 5 ];
  child_state->vars[ 10 ] = state->vars[ 10 ];
  child_state->vars[ 11 ] = state->vars[ 11 ];
  child_state->vars[ 12 ] = state->vars[ 12 ];
  child_state->vars[ 13 ] = state->vars[ 13 ];
  child_state->vars[ 14 ] = state->vars[ 14 ];
  child_state->vars[ 15 ] = state->vars[ 15 ];
}

static void fwdrule37( const state_t *state, state_t *child_state )
{
  child_state->vars[ 0 ] = state->vars[ 0 ];
  child_state->vars[ 1 ] = state->vars[ 1 ];
  child_state->vars[ 2 ] = state->vars[ 2 ];
  child_state->vars[ 3 ] = state->vars[ 3 ];
  child_state->vars[ 4 ] = state->vars[ 4 ];
  child_state->vars[ 5 ] = state->vars[ 5 ];
  child_state->vars[ 6 ] = state->vars[ 10 ];
  child_state->vars[ 7 ] = state->vars[ 7 ];
  child_state->vars[ 8 ] = state->vars[ 8 ];
  child_state->vars[ 9 ] = state->vars[ 9 ];
  child_state->vars[ 10 ] = 0;
  child_state->vars[ 11 ] = state->vars[ 11 ];
  child_state->vars[ 12 ] = state->vars[ 12 ];
  child_state->vars[ 13 ] = state->vars[ 13 ];
  child_state->vars[ 14 ] = state->vars[ 14 ];
  child_state->vars[ 15 ] = state->vars[ 15 ];
}

static void fwdrule38( const state_t *state, state_t *child_state )
{
  child_state->vars[ 0 ] = state->vars[ 0 ];
  child_state->vars[ 1 ] = state->vars[ 1 ];
  child_state->vars[ 2 ] = state->vars[ 2 ];
  child_state->vars[ 3 ] = state->vars[ 3 ];
  child_state->vars[ 4 ] = state->vars[ 4 ];
  child_state->vars[ 5 ] = state->vars[ 5 ];
  child_state->vars[ 6 ] = 0;
  child_state->vars[ 7 ] = state->vars[ 7 ];
  child_state->vars[ 8 ] = state->vars[ 8 ];
  child_state->vars[ 9 ] = state->vars[ 9 ];
  child_state->vars[ 10 ] = state->vars[ 6 ];
  child_state->vars[ 11 ] = state->vars[ 11 ];
  child_state->vars[ 12 ] = state->vars[ 12 ];
  child_state->vars[ 13 ] = state->vars[ 13 ];
  child_state->vars[ 14 ] = state->vars[ 14 ];
  child_state->vars[ 15 ] = state->vars[ 15 ];
}

static void fwdrule39( const state_t *state, state_t *child_state )
{
  child_state->vars[ 0 ] = state->vars[ 0 ];
  child_state->vars[ 1 ] = state->vars[ 1 ];
  child_state->vars[ 2 ] = state->vars[ 2 ];
  child_state->vars[ 3 ] = state->vars[ 3 ];
  child_state->vars[ 4 ] = state->vars[ 4 ];
  child_state->vars[ 5 ] = state->vars[ 5 ];
  child_state->vars[ 6 ] = state->vars[ 6 ];
  child_state->vars[ 7 ] = state->vars[ 11 ];
  child_state->vars[ 8 ] = state->vars[ 8 ];
  child_state->vars[ 9 ] = state->vars[ 9 ];
  child_state->vars[ 10 ] = state->vars[ 10 ];
  child_state->vars[ 11 ] = 0;
  child_state->vars[ 12 ] = state->vars[ 12 ];
  child_state->vars[ 13 ] = state->vars[ 13 ];
  child_state->vars[ 14 ] = state->vars[ 14 ];
  child_state->vars[ 15 ] = state->vars[ 15 ];
}

static void fwdrule40( const state_t *state, state_t *child_state )
{
  child_state->vars[ 0 ] = state->vars[ 0 ];
  child_state->vars[ 1 ] = state->vars[ 1 ];
  child_state->vars[ 2 ] = state->vars[ 2 ];
  child_state->vars[ 3 ] = state->vars[ 3 ];
  child_state->vars[ 4 ] = state->vars[ 4 ];
  child_state->vars[ 5 ] = state->vars[ 5 ];
  child_state->vars[ 6 ] = state->vars[ 6 ];
  child_state->vars[ 7 ] = 0;
  child_state->vars[ 8 ] = state->vars[ 8 ];
  child_state->vars[ 9 ] = state->vars[ 9 ];
  child_state->vars[ 10 ] = state->vars[ 10 ];
  child_state->vars[ 11 ] = state->vars[ 7 ];
  child_state->vars[ 12 ] = state->vars[ 12 ];
  child_state->vars[ 13 ] = state->vars[ 13 ];
  child_state->vars[ 14 ] = state->vars[ 14 ];
  child_state->vars[ 15 ] = state->vars[ 15 ];
}

static void fwdrule41( const state_t *state, state_t *child_state )
{
  child_state->vars[ 0 ] = state->vars[ 0 ];
  child_state->vars[ 1 ] = state->vars[ 1 ];
  child_state->vars[ 2 ] = state->vars[ 2 ];
  child_state->vars[ 3 ] = state->vars[ 3 ];
  child_state->vars[ 4 ] = state->vars[ 4 ];
  child_state->vars[ 5 ] = state->vars[ 5 ];
  child_state->vars[ 6 ] = state->vars[ 6 ];
  child_state->vars[ 7 ] = state->vars[ 7 ];
  child_state->vars[ 8 ] = state->vars[ 12 ];
  child_state->vars[ 9 ] = state->vars[ 9 ];
  child_state->vars[ 10 ] = state->vars[ 10 ];
  child_state->vars[ 11 ] = state->vars[ 11 ];
  child_state->vars[ 12 ] = 0;
  child_state->vars[ 13 ] = state->vars[ 13 ];
  child_state->vars[ 14 ] = state->vars[ 14 ];
  child_state->vars[ 15 ] = state->vars[ 15 ];
}

static void fwdrule42( const state_t *state, state_t *child_state )
{
  child_state->vars[ 0 ] = state->vars[ 0 ];
  child_state->vars[ 1 ] = state->vars[ 1 ];
  child_state->vars[ 2 ] = state->vars[ 2 ];
  child_state->vars[ 3 ] = state->vars[ 3 ];
  child_state->vars[ 4 ] = state->vars[ 4 ];
  child_state->vars[ 5 ] = state->vars[ 5 ];
  child_state->vars[ 6 ] = state->vars[ 6 ];
  child_state->vars[ 7 ] = state->vars[ 7 ];
  child_state->vars[ 8 ] = 0;
  child_state->vars[ 9 ] = state->vars[ 9 ];
  child_state->vars[ 10 ] = state->vars[ 10 ];
  child_state->vars[ 11 ] = state->vars[ 11 ];
  child_state->vars[ 12 ] = state->vars[ 8 ];
  child_state->vars[ 13 ] = state->vars[ 13 ];
  child_state->vars[ 14 ] = state->vars[ 14 ];
  child_state->vars[ 15 ] = state->vars[ 15 ];
}

static void fwdrule43( const state_t *state, state_t *child_state )
{
  child_state->vars[ 0 ] = state->vars[ 0 ];
  child_state->vars[ 1 ] = state->vars[ 1 ];
  child_state->vars[ 2 ] = state->vars[ 2 ];
  child_state->vars[ 3 ] = state->vars[ 3 ];
  child_state->vars[ 4 ] = state->vars[ 4 ];
  child_state->vars[ 5 ] = state->vars[ 5 ];
  child_state->vars[ 6 ] = state->vars[ 6 ];
  child_state->vars[ 7 ] = state->vars[ 7 ];
  child_state->vars[ 8 ] = state->vars[ 8 ];
  child_state->vars[ 9 ] = state->vars[ 13 ];
  child_state->vars[ 10 ] = state->vars[ 10 ];
  child_state->vars[ 11 ] = state->vars[ 11 ];
  child_state->vars[ 12 ] = state->vars[ 12 ];
  child_state->vars[ 13 ] = 0;
  child_state->vars[ 14 ] = state->vars[ 14 ];
  child_state->vars[ 15 ] = state->vars[ 15 ];
}

static void fwdrule44( const state_t *state, state_t *child_state )
{
  child_state->vars[ 0 ] = state->vars[ 0 ];
  child_state->vars[ 1 ] = state->vars[ 1 ];
  child_state->vars[ 2 ] = state->vars[ 2 ];
  child_state->vars[ 3 ] = state->vars[ 3 ];
  child_state->vars[ 4 ] = state->vars[ 4 ];
  child_state->vars[ 5 ] = state->vars[ 5 ];
  child_state->vars[ 6 ] = state->vars[ 6 ];
  child_state->vars[ 7 ] = state->vars[ 7 ];
  child_state->vars[ 8 ] = state->vars[ 8 ];
  child_state->vars[ 9 ] = 0;
  child_state->vars[ 10 ] = state->vars[ 10 ];
  child_state->vars[ 11 ] = state->vars[ 11 ];
  child_state->vars[ 12 ] = state->vars[ 12 ];
  child_state->vars[ 13 ] = state->vars[ 9 ];
  child_state->vars[ 14 ] = state->vars[ 14 ];
  child_state->vars[ 15 ] = state->vars[ 15 ];
}

static void fwdrule45( const state_t *state, state_t *child_state )
{
  child_state->vars[ 0 ] = state->vars[ 0 ];
  child_state->vars[ 1 ] = state->vars[ 1 ];
  child_state->vars[ 2 ] = state->vars[ 2 ];
  child_state->vars[ 3 ] = state->vars[ 3 ];
  child_state->vars[ 4 ] = state->vars[ 4 ];
  child_state->vars[ 5 ] = state->vars[ 5 ];
  child_state->vars[ 6 ] = state->vars[ 6 ];
  child_state->vars[ 7 ] = state->vars[ 7 ];
  child_state->vars[ 8 ] = state->vars[ 8 ];
  child_state->vars[ 9 ] = state->vars[ 9 ];
  child_state->vars[ 10 ] = state->vars[ 14 ];
  child_state->vars[ 11 ] = state->vars[ 11 ];
  child_state->vars[ 12 ] = state->vars[ 12 ];
  child_state->vars[ 13 ] = state->vars[ 13 ];
  child_state->vars[ 14 ] = 0;
  child_state->vars[ 15 ] = state->vars[ 15 ];
}

static void fwdrule46( const state_t *state, state_t *child_state )
{
  child_state->vars[ 0 ] = state->vars[ 0 ];
  child_state->vars[ 1 ] = state->vars[ 1 ];
  child_state->vars[ 2 ] = state->vars[ 2 ];
  child_state->vars[ 3 ] = state->vars[ 3 ];
  child_state->vars[ 4 ] = state->vars[ 4 ];
  child_state->vars[ 5 ] = state->vars[ 5 ];
  child_state->vars[ 6 ] = state->vars[ 6 ];
  child_state->vars[ 7 ] = state->vars[ 7 ];
  child_state->vars[ 8 ] = state->vars[ 8 ];
  child_state->vars[ 9 ] = state->vars[ 9 ];
  child_state->vars[ 10 ] = 0;
  child_state->vars[ 11 ] = state->vars[ 11 ];
  child_state->vars[ 12 ] = state->vars[ 12 ];
  child_state->vars[ 13 ] = state->vars[ 13 ];
  child_state->vars[ 14 ] = state->vars[ 10 ];
  child_state->vars[ 15 ] = state->vars[ 15 ];
}

static void fwdrule47( const state_t *state, state_t *child_state )
{
  child_state->vars[ 0 ] = state->vars[ 0 ];
  child_state->vars[ 1 ] = state->vars[ 1 ];
  child_state->vars[ 2 ] = state->vars[ 2 ];
  child_state->vars[ 3 ] = state->vars[ 3 ];
  child_state->vars[ 4 ] = state->vars[ 4 ];
  child_state->vars[ 5 ] = state->vars[ 5 ];
  child_state->vars[ 6 ] = state->vars[ 6 ];
  child_state->vars[ 7 ] = state->vars[ 7 ];
  child_state->vars[ 8 ] = state->vars[ 8 ];
  child_state->vars[ 9 ] = state->vars[ 9 ];
  child_state->vars[ 10 ] = state->vars[ 10 ];
  child_state->vars[ 11 ] = state->vars[ 15 ];
  child_state->vars[ 12 ] = state->vars[ 12 ];
  child_state->vars[ 13 ] = state->vars[ 13 ];
  child_state->vars[ 14 ] = state->vars[ 14 ];
  child_state->vars[ 15 ] = 0;
}

static void fwdrule48( const state_t *state, state_t *child_state )
{
  child_state->vars[ 0 ] = state->vars[ 0 ];
  child_state->vars[ 1 ] = state->vars[ 1 ];
  child_state->vars[ 2 ] = state->vars[ 2 ];
  child_state->vars[ 3 ] = state->vars[ 3 ];
  child_state->vars[ 4 ] = state->vars[ 4 ];
  child_state->vars[ 5 ] = state->vars[ 5 ];
  child_state->vars[ 6 ] = state->vars[ 6 ];
  child_state->vars[ 7 ] = state->vars[ 7 ];
  child_state->vars[ 8 ] = state->vars[ 8 ];
  child_state->vars[ 9 ] = state->vars[ 9 ];
  child_state->vars[ 10 ] = state->vars[ 10 ];
  child_state->vars[ 11 ] = 0;
  child_state->vars[ 12 ] = state->vars[ 12 ];
  child_state->vars[ 13 ] = state->vars[ 13 ];
  child_state->vars[ 14 ] = state->vars[ 14 ];
  child_state->vars[ 15 ] = state->vars[ 11 ];
}

static actfuncptr fwd_rules[ 48 ] = { fwdrule1, fwdrule2, fwdrule3, fwdrule4, fwdrule5, fwdrule6, fwdrule7, fwdrule8, fwdrule9, fwdrule10, fwdrule11, fwdrule12, fwdrule13, fwdrule14, fwdrule15, fwdrule16, fwdrule17, fwdrule18, fwdrule19, fwdrule20, fwdrule21, fwdrule22, fwdrule23, fwdrule24, fwdrule25, fwdrule26, fwdrule27, fwdrule28, fwdrule29, fwdrule30, fwdrule31, fwdrule32, fwdrule33, fwdrule34, fwdrule35, fwdrule36, fwdrule37, fwdrule38, fwdrule39, fwdrule40, fwdrule41, fwdrule42, fwdrule43, fwdrule44, fwdrule45, fwdrule46, fwdrule47, fwdrule48 };

static int fwdfn15_a0_3( const state_t *state, void *next_func )
{
  *((funcptr *)next_func) = NULL;
  return 44;
}

static int fwdfn15_a0_2( const state_t *state, void *next_func )
{
  *((funcptr *)next_func) = fwdfn15_a0_3;
  return 37;
}

static int fwdfn15_a0_1( const state_t *state, void *next_func )
{
  *((funcptr *)next_func) = fwdfn15_a0_2;
  return 16;
}

static int fwdfn15( const state_t *state, void *next_func )
{
  if( state->vars[ 10 ] == 0 ) {
    *((funcptr *)next_func) = fwdfn15_a0_1;
    return 15;
  } else {
    return -1;
  }
}

static int fwdfn14_a0_3( const state_t *state, void *next_func )
{
  *((funcptr *)next_func) = fwdfn15;
  return 42;
}

static int fwdfn14_a0_2( const state_t *state, void *next_func )
{
  *((funcptr *)next_func) = fwdfn14_a0_3;
  return 35;
}

static int fwdfn14_a0_1( const state_t *state, void *next_func )
{
  *((funcptr *)next_func) = fwdfn14_a0_2;
  return 14;
}

static int fwdfn14( const state_t *state, void *next_func )
{
  if( state->vars[ 9 ] == 0 ) {
    *((funcptr *)next_func) = fwdfn14_a0_1;
    return 13;
  } else {
    return fwdfn15( state, next_func );
  }
}

static int fwdfn13_a0_3( const state_t *state, void *next_func )
{
  *((funcptr *)next_func) = fwdfn14;
  return 36;
}

static int fwdfn13_a0_2( const state_t *state, void *next_func )
{
  *((funcptr *)next_func) = fwdfn13_a0_3;
  return 29;
}

static int fwdfn13_a0_1( const state_t *state, void *next_func )
{
  *((funcptr *)next_func) = fwdfn13_a0_2;
  return 10;
}

static int fwdfn13( const state_t *state, void *next_func )
{
  if( state->vars[ 6 ] == 0 ) {
    *((funcptr *)next_func) = fwdfn13_a0_1;
    return 9;
  } else {
    return fwdfn14( state, next_func );
  }
}

static int fwdfn12_a0_3( const state_t *state, void *next_func )
{
  *((funcptr *)next_func) = fwdfn13;
  return 34;
}

static int fwdfn12_a0_2( const state_t *state, void *next_func )
{
  *((funcptr *)next_func) = fwdfn12_a0_3;
  return 27;
}

static int fwdfn12_a0_1( const state_t *state, void *next_func )
{
  *((funcptr *)next_func) = fwdfn12_a0_2;
  return 8;
}

static int fwdfn12( const state_t *state, void *next_func )
{
  if( state->vars[ 5 ] == 0 ) {
    *((funcptr *)next_func) = fwdfn12_a0_1;
    return 7;
  } else {
    return fwdfn13( state, next_func );
  }
}

static int fwdfn11_a0_2( const state_t *state, void *next_func )
{
  *((funcptr *)next_func) = fwdfn12;
  return 45;
}

static int fwdfn11_a0_1( const state_t *state, void *next_func )
{
  *((funcptr *)next_func) = fwdfn11_a0_2;
  return 22;
}

static int fwdfn11( const state_t *state, void *next_func )
{
  if( state->vars[ 14 ] == 0 ) {
    *((funcptr *)next_func) = fwdfn11_a0_1;
    return 21;
  } else {
    return fwdfn12( state, next_func );
  }
}

static int fwdfn10_a0_2( const state_t *state, void *next_func )
{
  *((funcptr *)next_func) = fwdfn11;
  return 43;
}

static int fwdfn10_a0_1( const state_t *state, void *next_func )
{
  *((funcptr *)next_func) = fwdfn10_a0_2;
  return 20;
}

static int fwdfn10( const state_t *state, void *next_func )
{
  if( state->vars[ 13 ] == 0 ) {
    *((funcptr *)next_func) = fwdfn10_a0_1;
    return 19;
  } else {
    return fwdfn11( state, next_func );
  }
}

static int fwdfn9_a0_2( const state_t *state, void *next_func )
{
  *((funcptr *)next_func) = fwdfn10;
  return 46;
}

static int fwdfn9_a0_1( const state_t *state, void *next_func )
{
  *((funcptr *)next_func) = fwdfn9_a0_2;
  return 39;
}

static int fwdfn9( const state_t *state, void *next_func )
{
  if( state->vars[ 11 ] == 0 ) {
    *((funcptr *)next_func) = fwdfn9_a0_1;
    return 17;
  } else {
    return fwdfn10( state, next_func );
  }
}

static int fwdfn8_a0_2( const state_t *state, void *next_func )
{
  *((funcptr *)next_func) = fwdfn9;
  return 40;
}

static int fwdfn8_a0_1( const state_t *state, void *next_func )
{
  *((funcptr *)next_func) = fwdfn8_a0_2;
  return 33;
}

static int fwdfn8( const state_t *state, void *next_func )
{
  if( state->vars[ 8 ] == 0 ) {
    *((funcptr *)next_func) = fwdfn8_a0_1;
    return 12;
  } else {
    return fwdfn9( state, next_func );
  }
}

static int fwdfn7_a0_2( const state_t *state, void *next_func )
{
  *((funcptr *)next_func) = fwdfn8;
  return 38;
}

static int fwdfn7_a0_1( const state_t *state, void *next_func )
{
  *((funcptr *)next_func) = fwdfn7_a0_2;
  return 31;
}

static int fwdfn7( const state_t *state, void *next_func )
{
  if( state->vars[ 7 ] == 0 ) {
    *((funcptr *)next_func) = fwdfn7_a0_1;
    return 11;
  } else {
    return fwdfn8( state, next_func );
  }
}

static int fwdfn6_a0_2( const state_t *state, void *next_func )
{
  *((funcptr *)next_func) = fwdfn7;
  return 32;
}

static int fwdfn6_a0_1( const state_t *state, void *next_func )
{
  *((funcptr *)next_func) = fwdfn6_a0_2;
  return 25;
}

static int fwdfn6( const state_t *state, void *next_func )
{
  if( state->vars[ 4 ] == 0 ) {
    *((funcptr *)next_func) = fwdfn6_a0_1;
    return 6;
  } else {
    return fwdfn7( state, next_func );
  }
}

static int fwdfn5_a0_2( const state_t *state, void *next_func )
{
  *((funcptr *)next_func) = fwdfn6;
  return 28;
}

static int fwdfn5_a0_1( const state_t *state, void *next_func )
{
  *((funcptr *)next_func) = fwdfn5_a0_2;
  return 4;
}

static int fwdfn5( const state_t *state, void *next_func )
{
  if( state->vars[ 2 ] == 0 ) {
    *((funcptr *)next_func) = fwdfn5_a0_1;
    return 3;
  } else {
    return fwdfn6( state, next_func );
  }
}

static int fwdfn4_a0_2( const state_t *state, void *next_func )
{
  *((funcptr *)next_func) = fwdfn5;
  return 26;
}

static int fwdfn4_a0_1( const state_t *state, void *next_func )
{
  *((funcptr *)next_func) = fwdfn4_a0_2;
  return 2;
}

static int fwdfn4( const state_t *state, void *next_func )
{
  if( state->vars[ 1 ] == 0 ) {
    *((funcptr *)next_func) = fwdfn4_a0_1;
    return 1;
  } else {
    return fwdfn5( state, next_func );
  }
}

static int fwdfn3_a0_1( const state_t *state, void *next_func )
{
  *((funcptr *)next_func) = fwdfn4;
  return 47;
}

static int fwdfn3( const state_t *state, void *next_func )
{
  if( state->vars[ 15 ] == 0 ) {
    *((funcptr *)next_func) = fwdfn3_a0_1;
    return 23;
  } else {
    return fwdfn4( state, next_func );
  }
}

static int fwdfn2_a0_1( const state_t *state, void *next_func )
{
  *((funcptr *)next_func) = fwdfn3;
  return 41;
}

static int fwdfn2( const state_t *state, void *next_func )
{
  if( state->vars[ 12 ] == 0 ) {
    *((funcptr *)next_func) = fwdfn2_a0_1;
    return 18;
  } else {
    return fwdfn3( state, next_func );
  }
}

static int fwdfn1_a0_1( const state_t *state, void *next_func )
{
  *((funcptr *)next_func) = fwdfn2;
  return 30;
}

static int fwdfn1( const state_t *state, void *next_func )
{
  if( state->vars[ 3 ] == 0 ) {
    *((funcptr *)next_func) = fwdfn1_a0_1;
    return 5;
  } else {
    return fwdfn2( state, next_func );
  }
}

static int fwdfn0_a0_1( const state_t *state, void *next_func )
{
  *((funcptr *)next_func) = fwdfn1;
  return 24;
}

static int fwdfn0( const state_t *state, void *next_func )
{
  if( state->vars[ 0 ] == 0 ) {
    *((funcptr *)next_func) = fwdfn0_a0_1;
    return 0;
  } else {
    return fwdfn1( state, next_func );
  }
}

static int bwd_prune_table[ 2352 ] = { 48, 96, 144, 192, 240, 288, 336, 384, 432, 480, 528, 576, 624, 672, 720, 768, 816, 864, 912, 960, 1008, 1056, 1104, 1152, 1200, 1248, 1296, 1344, 1392, 1440, 1488, 1536, 1584, 1632, 1680, 1728, 1776, 1824, 1872, 1920, 1968, 2016, 2064, 2112, 2160, 2208, 2256, 2304, 0, 0, 144, 0, 240, 288, 336, 384, 432, 480, 528, 576, 624, 672, 720, 768, 816, 864, 912, 960, 1008, 1056, 1104, 1152, 0, 1248, 1296, 0, 1392, 1440, 1488, 1536, 1584, 1632, 1680, 1728, 1776, 1824, 1872, 1920, 1968, 2016, 2064, 2112, 2160, 2208, 2256, 2304, 0, 0, 0, 192, 240, 288, 336, 384, 432, 480, 528, 576, 624, 672, 720, 768, 816, 864, 912, 960, 1008, 1056, 1104, 1152, 1200, 0, 0, 1344, 1392, 1440, 1488, 1536, 1584, 1632, 1680, 1728, 1776, 1824, 1872, 1920, 1968, 2016, 2064, 2112, 2160, 2208, 2256, 2304, 48, 0, 0, 0, 240, 0, 336, 384, 432, 480, 528, 576, 624, 672, 720, 768, 816, 864, 912, 960, 1008, 1056, 1104, 1152, 1200, 1248, 0, 1344, 1392, 0, 1488, 1536, 1584, 1632, 1680, 1728, 1776, 1824, 1872, 1920, 1968, 2016, 2064, 2112, 2160, 2208, 2256, 2304, 0, 96, 0, 0, 0, 288, 336, 384, 432, 480, 528, 576, 624, 672, 720, 768, 816, 864, 912, 960, 1008, 1056, 1104, 1152, 1200, 1248, 1296, 0, 0, 1440, 1488, 1536, 1584, 1632, 1680, 1728, 1776, 1824, 1872, 1920, 1968, 2016, 2064, 2112, 2160, 2208, 2256, 2304, 0, 0, 144, 0, 0, 0, 336, 384, 432, 480, 528, 576, 624, 672, 720, 768, 816, 864, 912, 960, 1008, 1056, 1104, 1152, 1200, 1248, 1296, 1344, 0, 1440, 1488, 0, 1584, 1632, 1680, 1728, 1776, 1824, 1872, 1920, 1968, 2016, 2064, 2112, 2160, 2208, 2256, 2304, 0, 0, 0, 192, 0, 0, 336, 384, 432, 480, 528, 576, 624, 672, 720, 768, 816, 864, 912, 960, 1008, 1056, 1104, 1152, 1200, 1248, 1296, 1344, 1392, 0, 0, 1536, 1584, 1632, 1680, 1728, 1776, 1824, 1872, 1920, 1968, 2016, 2064, 2112, 2160, 2208, 2256, 2304, 0, 0, 0, 0, 0, 0, 0, 0, 432, 0, 528, 576, 624, 672, 720, 768, 816, 864, 912, 960, 1008, 1056, 1104, 1152, 1200, 0, 0, 1344, 1392, 1440, 1488, 1536, 0, 1632, 1680, 0, 1776, 1824, 1872, 1920, 1968, 2016, 2064, 2112, 2160, 2208, 2256, 2304, 0, 0, 0, 0, 0, 0, 0, 0, 0, 480, 528, 576, 624, 672, 720, 768, 816, 864, 912, 960, 1008, 1056, 1104, 1152, 0, 1248, 1296, 0, 1392, 1440, 1488, 1536, 1584, 0, 0, 1728, 1776, 1824, 1872, 1920, 1968, 2016, 2064, 2112, 2160, 2208, 2256, 2304, 0, 0, 0, 0, 0, 0, 336, 0, 0, 0, 528, 0, 624, 672, 720, 768, 816, 864, 912, 960, 1008, 1056, 1104, 1152, 1200, 1248, 1296, 0, 0, 1440, 1488, 1536, 1584, 1632, 0, 1728, 1776, 0, 1872, 1920, 1968, 2016, 2064, 2112, 2160, 2208, 2256, 2304, 0, 0, 0, 0, 0, 0, 0, 384, 0, 0, 0, 576, 624, 672, 720, 768, 816, 864, 912, 960, 1008, 1056, 1104, 1152, 1200, 1248, 0, 1344, 1392, 0, 1488, 1536, 1584, 1632, 1680, 0, 0, 1824, 1872, 1920, 1968, 2016, 2064, 2112, 2160, 2208, 2256, 2304, 0, 0, 0, 0, 0, 0, 0, 0, 432, 0, 0, 0, 624, 672, 720, 768, 816, 864, 912, 960, 1008, 1056, 1104, 1152, 1200, 1248, 1296, 1344, 1392, 0, 0, 1536, 1584, 1632, 1680, 1728, 0, 1824, 1872, 0, 1968, 2016, 2064, 2112, 2160, 2208, 2256, 2304, 0, 0, 0, 0, 0, 0, 0, 0, 0, 480, 0, 0, 624, 672, 720, 768, 816, 864, 912, 960, 1008, 1056, 1104, 1152, 1200, 1248, 1296, 1344, 0, 1440, 1488, 0, 1584, 1632, 1680, 1728, 1776, 0, 0, 1920, 1968, 2016, 2064, 2112, 2160, 2208, 2256, 2304, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 720, 0, 816, 864, 912, 960, 1008, 1056, 1104, 1152, 1200, 1248, 1296, 1344, 1392, 1440, 1488, 1536, 1584, 0, 0, 1728, 1776, 1824, 1872, 1920, 0, 2016, 2064, 0, 2160, 2208, 2256, 2304, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 768, 816, 864, 912, 960, 1008, 1056, 1104, 1152, 1200, 1248, 1296, 1344, 1392, 1440, 1488, 1536, 0, 1632, 1680, 0, 1776, 1824, 1872, 1920, 1968, 0, 0, 2112, 2160, 2208, 2256, 2304, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 624, 0, 0, 0, 816, 0, 912, 960, 1008, 1056, 1104, 1152, 1200, 1248, 1296, 1344, 1392, 1440, 1488, 1536, 1584, 1632, 1680, 0, 0, 1824, 1872, 1920, 1968, 2016, 0, 2112, 2160, 0, 2256, 2304, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 672, 0, 0, 0, 864, 912, 960, 1008, 1056, 1104, 1152, 1200, 1248, 1296, 1344, 1392, 1440, 1488, 1536, 1584, 1632, 0, 1728, 1776, 0, 1872, 1920, 1968, 2016, 2064, 0, 0, 2208, 2256, 2304, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 720, 0, 0, 0, 912, 960, 1008, 1056, 1104, 1152, 1200, 1248, 1296, 1344, 1392, 1440, 1488, 1536, 1584, 1632, 1680, 1728, 1776, 0, 0, 1920, 1968, 2016, 2064, 2112, 0, 2208, 2256, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 768, 0, 0, 912, 960, 1008, 1056, 1104, 1152, 1200, 1248, 1296, 1344, 1392, 1440, 1488, 1536, 1584, 1632, 1680, 1728, 0, 1824, 1872, 0, 1968, 2016, 2064, 2112, 2160, 0, 0, 2304, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1008, 0, 1104, 1152, 1200, 1248, 1296, 1344, 1392, 1440, 1488, 1536, 1584, 1632, 1680, 1728, 1776, 1824, 1872, 1920, 1968, 0, 0, 2112, 2160, 2208, 2256, 2304, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1056, 1104, 1152, 1200, 1248, 1296, 1344, 1392, 1440, 1488, 1536, 1584, 1632, 1680, 1728, 1776, 1824, 1872, 1920, 0, 2016, 2064, 0, 2160, 2208, 2256, 2304, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 912, 0, 0, 0, 1104, 0, 1200, 1248, 1296, 1344, 1392, 1440, 1488, 1536, 1584, 1632, 1680, 1728, 1776, 1824, 1872, 1920, 1968, 2016, 2064, 0, 0, 2208, 2256, 2304, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 960, 0, 0, 0, 1152, 1200, 1248, 1296, 1344, 1392, 1440, 1488, 1536, 1584, 1632, 1680, 1728, 1776, 1824, 1872, 1920, 1968, 2016, 0, 2112, 2160, 0, 2256, 2304, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1008, 0, 0, 0, 1200, 1248, 1296, 1344, 1392, 1440, 1488, 1536, 1584, 1632, 1680, 1728, 1776, 1824, 1872, 1920, 1968, 2016, 2064, 2112, 2160, 0, 0, 2304, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1056, 0, 0, 1200, 1248, 1296, 1344, 1392, 1440, 1488, 1536, 1584, 1632, 1680, 1728, 1776, 1824, 1872, 1920, 1968, 2016, 2064, 2112, 0, 2208, 2256, 0, 0, 96, 0, 0, 0, 0, 336, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1296, 1344, 1392, 1440, 1488, 1536, 1584, 0, 1680, 1728, 1776, 1824, 1872, 1920, 1968, 2016, 2064, 2112, 2160, 2208, 2256, 2304, 48, 0, 0, 0, 0, 0, 0, 384, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1296, 1344, 1392, 1440, 1488, 1536, 0, 1632, 1680, 1728, 1776, 1824, 1872, 1920, 1968, 2016, 2064, 2112, 2160, 2208, 2256, 2304, 48, 0, 0, 192, 0, 0, 0, 384, 432, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1392, 1440, 1488, 1536, 1584, 1632, 1680, 0, 1776, 1824, 1872, 1920, 1968, 2016, 2064, 2112, 2160, 2208, 2256, 2304, 0, 96, 144, 0, 0, 0, 336, 0, 0, 480, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1392, 1440, 1488, 1536, 1584, 1632, 0, 1728, 1776, 1824, 1872, 1920, 1968, 2016, 2064, 2112, 2160, 2208, 2256, 2304, 0, 0, 144, 0, 0, 288, 0, 0, 0, 480, 528, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1488, 1536, 1584, 1632, 1680, 1728, 1776, 0, 1872, 1920, 1968, 2016, 2064, 2112, 2160, 2208, 2256, 2304, 0, 0, 0, 192, 240, 0, 0, 0, 432, 0, 0, 576, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1488, 1536, 1584, 1632, 1680, 1728, 0, 1824, 1872, 1920, 1968, 2016, 2064, 2112, 2160, 2208, 2256, 2304, 0, 0, 0, 0, 240, 0, 0, 0, 0, 0, 0, 576, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1584, 1632, 1680, 1728, 1776, 1824, 1872, 0, 1968, 2016, 2064, 2112, 2160, 2208, 2256, 2304, 0, 0, 0, 0, 0, 288, 0, 0, 0, 0, 528, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1584, 1632, 1680, 1728, 1776, 1824, 0, 1920, 1968, 2016, 2064, 2112, 2160, 2208, 2256, 2304, 0, 0, 0, 0, 0, 0, 0, 384, 0, 0, 0, 0, 624, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1200, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1680, 1728, 1776, 1824, 1872, 1920, 1968, 0, 2064, 2112, 2160, 2208, 2256, 2304, 0, 0, 0, 0, 0, 0, 336, 0, 0, 0, 0, 0, 0, 672, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1248, 0, 0, 0, 0, 0, 0, 0, 0, 1680, 1728, 1776, 1824, 1872, 1920, 0, 2016, 2064, 2112, 2160, 2208, 2256, 2304, 0, 0, 0, 0, 0, 0, 336, 0, 0, 480, 0, 0, 0, 672, 720, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1296, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1776, 1824, 1872, 1920, 1968, 2016, 2064, 0, 2160, 2208, 2256, 2304, 0, 0, 0, 0, 0, 0, 0, 384, 432, 0, 0, 0, 624, 0, 0, 768, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1344, 0, 0, 0, 0, 0, 0, 0, 0, 1776, 1824, 1872, 1920, 1968, 2016, 0, 2112, 2160, 2208, 2256, 2304, 0, 0, 0, 0, 0, 0, 0, 0, 432, 0, 0, 576, 0, 0, 0, 768, 816, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1392, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1872, 1920, 1968, 2016, 2064, 2112, 2160, 0, 2256, 2304, 0, 0, 0, 0, 0, 0, 0, 0, 0, 480, 528, 0, 0, 0, 720, 0, 0, 864, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1440, 0, 0, 0, 0, 0, 0, 0, 0, 1872, 1920, 1968, 2016, 2064, 2112, 0, 2208, 2256, 2304, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 528, 0, 0, 0, 0, 0, 0, 864, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1488, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1968, 2016, 2064, 2112, 2160, 2208, 2256, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 576, 0, 0, 0, 0, 816, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1536, 0, 0, 0, 0, 0, 0, 0, 0, 1968, 2016, 2064, 2112, 2160, 2208, 0, 2304, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 672, 0, 0, 0, 0, 912, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1584, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2064, 2112, 2160, 2208, 2256, 2304, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 624, 0, 0, 0, 0, 0, 0, 960, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1632, 0, 0, 0, 0, 0, 0, 0, 0, 2064, 2112, 2160, 2208, 2256, 2304, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 624, 0, 0, 768, 0, 0, 0, 960, 1008, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1680, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2160, 2208, 2256, 2304, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 672, 720, 0, 0, 0, 912, 0, 0, 1056, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1728, 0, 0, 0, 0, 0, 0, 0, 0, 2160, 2208, 2256, 2304, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 720, 0, 0, 864, 0, 0, 0, 1056, 1104, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1776, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2256, 2304, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 768, 816, 0, 0, 0, 1008, 0, 0, 1152, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1824, 0, 0, 0, 0, 0, 0, 0, 0, 2256, 2304, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 816, 0, 0, 0, 0, 0, 0, 1152, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1872, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 864, 0, 0, 0, 0, 1104, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1920, 0, 0, 0, 0, 0, 0, 0, 0 };

static void bwdrule1( const state_t *state, state_t *child_state )
{
  child_state->vars[ 0 ] = 0;
  child_state->vars[ 1 ] = state->vars[ 0 ];
  child_state->vars[ 2 ] = state->vars[ 2 ];
  child_state->vars[ 3 ] = state->vars[ 3 ];
  child_state->vars[ 4 ] = state->vars[ 4 ];
  child_state->vars[ 5 ] = state->vars[ 5 ];
  child_state->vars[ 6 ] = state->vars[ 6 ];
  child_state->vars[ 7 ] = state->vars[ 7 ];
  child_state->vars[ 8 ] = state->vars[ 8 ];
  child_state->vars[ 9 ] = state->vars[ 9 ];
  child_state->vars[ 10 ] = state->vars[ 10 ];
  child_state->vars[ 11 ] = state->vars[ 11 ];
  child_state->vars[ 12 ] = state->vars[ 12 ];
  child_state->vars[ 13 ] = state->vars[ 13 ];
  child_state->vars[ 14 ] = state->vars[ 14 ];
  child_state->vars[ 15 ] = state->vars[ 15 ];
}

static void bwdrule2( const state_t *state, state_t *child_state )
{
  child_state->vars[ 0 ] = state->vars[ 1 ];
  child_state->vars[ 1 ] = 0;
  child_state->vars[ 2 ] = state->vars[ 2 ];
  child_state->vars[ 3 ] = state->vars[ 3 ];
  child_state->vars[ 4 ] = state->vars[ 4 ];
  child_state->vars[ 5 ] = state->vars[ 5 ];
  child_state->vars[ 6 ] = state->vars[ 6 ];
  child_state->vars[ 7 ] = state->vars[ 7 ];
  child_state->vars[ 8 ] = state->vars[ 8 ];
  child_state->vars[ 9 ] = state->vars[ 9 ];
  child_state->vars[ 10 ] = state->vars[ 10 ];
  child_state->vars[ 11 ] = state->vars[ 11 ];
  child_state->vars[ 12 ] = state->vars[ 12 ];
  child_state->vars[ 13 ] = state->vars[ 13 ];
  child_state->vars[ 14 ] = state->vars[ 14 ];
  child_state->vars[ 15 ] = state->vars[ 15 ];
}

static void bwdrule3( const state_t *state, state_t *child_state )
{
  child_state->vars[ 0 ] = state->vars[ 0 ];
  child_state->vars[ 1 ] = 0;
  child_state->vars[ 2 ] = state->vars[ 1 ];
  child_state->vars[ 3 ] = state->vars[ 3 ];
  child_state->vars[ 4 ] = state->vars[ 4 ];
  child_state->vars[ 5 ] = state->vars[ 5 ];
  child_state->vars[ 6 ] = state->vars[ 6 ];
  child_state->vars[ 7 ] = state->vars[ 7 ];
  child_state->vars[ 8 ] = state->vars[ 8 ];
  child_state->vars[ 9 ] = state->vars[ 9 ];
  child_state->vars[ 10 ] = state->vars[ 10 ];
  child_state->vars[ 11 ] = state->vars[ 11 ];
  child_state->vars[ 12 ] = state->vars[ 12 ];
  child_state->vars[ 13 ] = state->vars[ 13 ];
  child_state->vars[ 14 ] = state->vars[ 14 ];
  child_state->vars[ 15 ] = state->vars[ 15 ];
}

static void bwdrule4( const state_t *state, state_t *child_state )
{
  child_state->vars[ 0 ] = state->vars[ 0 ];
  child_state->vars[ 1 ] = state->vars[ 2 ];
  child_state->vars[ 2 ] = 0;
  child_state->vars[ 3 ] = state->vars[ 3 ];
  child_state->vars[ 4 ] = state->vars[ 4 ];
  child_state->vars[ 5 ] = state->vars[ 5 ];
  child_state->vars[ 6 ] = state->vars[ 6 ];
  child_state->vars[ 7 ] = state->vars[ 7 ];
  child_state->vars[ 8 ] = state->vars[ 8 ];
  child_state->vars[ 9 ] = state->vars[ 9 ];
  child_state->vars[ 10 ] = state->vars[ 10 ];
  child_state->vars[ 11 ] = state->vars[ 11 ];
  child_state->vars[ 12 ] = state->vars[ 12 ];
  child_state->vars[ 13 ] = state->vars[ 13 ];
  child_state->vars[ 14 ] = state->vars[ 14 ];
  child_state->vars[ 15 ] = state->vars[ 15 ];
}

static void bwdrule5( const state_t *state, state_t *child_state )
{
  child_state->vars[ 0 ] = state->vars[ 0 ];
  child_state->vars[ 1 ] = state->vars[ 1 ];
  child_state->vars[ 2 ] = 0;
  child_state->vars[ 3 ] = state->vars[ 2 ];
  child_state->vars[ 4 ] = state->vars[ 4 ];
  child_state->vars[ 5 ] = state->vars[ 5 ];
  child_state->vars[ 6 ] = state->vars[ 6 ];
  child_state->vars[ 7 ] = state->vars[ 7 ];
  child_state->vars[ 8 ] = state->vars[ 8 ];
  child_state->vars[ 9 ] = state->vars[ 9 ];
  child_state->vars[ 10 ] = state->vars[ 10 ];
  child_state->vars[ 11 ] = state->vars[ 11 ];
  child_state->vars[ 12 ] = state->vars[ 12 ];
  child_state->vars[ 13 ] = state->vars[ 13 ];
  child_state->vars[ 14 ] = state->vars[ 14 ];
  child_state->vars[ 15 ] = state->vars[ 15 ];
}

static void bwdrule6( const state_t *state, state_t *child_state )
{
  child_state->vars[ 0 ] = state->vars[ 0 ];
  child_state->vars[ 1 ] = state->vars[ 1 ];
  child_state->vars[ 2 ] = state->vars[ 3 ];
  child_state->vars[ 3 ] = 0;
  child_state->vars[ 4 ] = state->vars[ 4 ];
  child_state->vars[ 5 ] = state->vars[ 5 ];
  child_state->vars[ 6 ] = state->vars[ 6 ];
  child_state->vars[ 7 ] = state->vars[ 7 ];
  child_state->vars[ 8 ] = state->vars[ 8 ];
  child_state->vars[ 9 ] = state->vars[ 9 ];
  child_state->vars[ 10 ] = state->vars[ 10 ];
  child_state->vars[ 11 ] = state->vars[ 11 ];
  child_state->vars[ 12 ] = state->vars[ 12 ];
  child_state->vars[ 13 ] = state->vars[ 13 ];
  child_state->vars[ 14 ] = state->vars[ 14 ];
  child_state->vars[ 15 ] = state->vars[ 15 ];
}

static void bwdrule7( const state_t *state, state_t *child_state )
{
  child_state->vars[ 0 ] = state->vars[ 0 ];
  child_state->vars[ 1 ] = state->vars[ 1 ];
  child_state->vars[ 2 ] = state->vars[ 2 ];
  child_state->vars[ 3 ] = state->vars[ 3 ];
  child_state->vars[ 4 ] = 0;
  child_state->vars[ 5 ] = state->vars[ 4 ];
  child_state->vars[ 6 ] = state->vars[ 6 ];
  child_state->vars[ 7 ] = state->vars[ 7 ];
  child_state->vars[ 8 ] = state->vars[ 8 ];
  child_state->vars[ 9 ] = state->vars[ 9 ];
  child_state->vars[ 10 ] = state->vars[ 10 ];
  child_state->vars[ 11 ] = state->vars[ 11 ];
  child_state->vars[ 12 ] = state->vars[ 12 ];
  child_state->vars[ 13 ] = state->vars[ 13 ];
  child_state->vars[ 14 ] = state->vars[ 14 ];
  child_state->vars[ 15 ] = state->vars[ 15 ];
}

static void bwdrule8( const state_t *state, state_t *child_state )
{
  child_state->vars[ 0 ] = state->vars[ 0 ];
  child_state->vars[ 1 ] = state->vars[ 1 ];
  child_state->vars[ 2 ] = state->vars[ 2 ];
  child_state->vars[ 3 ] = state->vars[ 3 ];
  child_state->vars[ 4 ] = state->vars[ 5 ];
  child_state->vars[ 5 ] = 0;
  child_state->vars[ 6 ] = state->vars[ 6 ];
  child_state->vars[ 7 ] = state->vars[ 7 ];
  child_state->vars[ 8 ] = state->vars[ 8 ];
  child_state->vars[ 9 ] = state->vars[ 9 ];
  child_state->vars[ 10 ] = state->vars[ 10 ];
  child_state->vars[ 11 ] = state->vars[ 11 ];
  child_state->vars[ 12 ] = state->vars[ 12 ];
  child_state->vars[ 13 ] = state->vars[ 13 ];
  child_state->vars[ 14 ] = state->vars[ 14 ];
  child_state->vars[ 15 ] = state->vars[ 15 ];
}

static void bwdrule9( const state_t *state, state_t *child_state )
{
  child_state->vars[ 0 ] = state->vars[ 0 ];
  child_state->vars[ 1 ] = state->vars[ 1 ];
  child_state->vars[ 2 ] = state->vars[ 2 ];
  child_state->vars[ 3 ] = state->vars[ 3 ];
  child_state->vars[ 4 ] = state->vars[ 4 ];
  child_state->vars[ 5 ] = 0;
  child_state->vars[ 6 ] = state->vars[ 5 ];
  child_state->vars[ 7 ] = state->vars[ 7 ];
  child_state->vars[ 8 ] = state->vars[ 8 ];
  child_state->vars[ 9 ] = state->vars[ 9 ];
  child_state->vars[ 10 ] = state->vars[ 10 ];
  child_state->vars[ 11 ] = state->vars[ 11 ];
  child_state->vars[ 12 ] = state->vars[ 12 ];
  child_state->vars[ 13 ] = state->vars[ 13 ];
  child_state->vars[ 14 ] = state->vars[ 14 ];
  child_state->vars[ 15 ] = state->vars[ 15 ];
}

static void bwdrule10( const state_t *state, state_t *child_state )
{
  child_state->vars[ 0 ] = state->vars[ 0 ];
  child_state->vars[ 1 ] = state->vars[ 1 ];
  child_state->vars[ 2 ] = state->vars[ 2 ];
  child_state->vars[ 3 ] = state->vars[ 3 ];
  child_state->vars[ 4 ] = state->vars[ 4 ];
  child_state->vars[ 5 ] = state->vars[ 6 ];
  child_state->vars[ 6 ] = 0;
  child_state->vars[ 7 ] = state->vars[ 7 ];
  child_state->vars[ 8 ] = state->vars[ 8 ];
  child_state->vars[ 9 ] = state->vars[ 9 ];
  child_state->vars[ 10 ] = state->vars[ 10 ];
  child_state->vars[ 11 ] = state->vars[ 11 ];
  child_state->vars[ 12 ] = state->vars[ 12 ];
  child_state->vars[ 13 ] = state->vars[ 13 ];
  child_state->vars[ 14 ] = state->vars[ 14 ];
  child_state->vars[ 15 ] = state->vars[ 15 ];
}

static void bwdrule11( const state_t *state, state_t *child_state )
{
  child_state->vars[ 0 ] = state->vars[ 0 ];
  child_state->vars[ 1 ] = state->vars[ 1 ];
  child_state->vars[ 2 ] = state->vars[ 2 ];
  child_state->vars[ 3 ] = state->vars[ 3 ];
  child_state->vars[ 4 ] = state->vars[ 4 ];
  child_state->vars[ 5 ] = state->vars[ 5 ];
  child_state->vars[ 6 ] = 0;
  child_state->vars[ 7 ] = state->vars[ 6 ];
  child_state->vars[ 8 ] = state->vars[ 8 ];
  child_state->vars[ 9 ] = state->vars[ 9 ];
  child_state->vars[ 10 ] = state->vars[ 10 ];
  child_state->vars[ 11 ] = state->vars[ 11 ];
  child_state->vars[ 12 ] = state->vars[ 12 ];
  child_state->vars[ 13 ] = state->vars[ 13 ];
  child_state->vars[ 14 ] = state->vars[ 14 ];
  child_state->vars[ 15 ] = state->vars[ 15 ];
}

static void bwdrule12( const state_t *state, state_t *child_state )
{
  child_state->vars[ 0 ] = state->vars[ 0 ];
  child_state->vars[ 1 ] = state->vars[ 1 ];
  child_state->vars[ 2 ] = state->vars[ 2 ];
  child_state->vars[ 3 ] = state->vars[ 3 ];
  child_state->vars[ 4 ] = state->vars[ 4 ];
  child_state->vars[ 5 ] = state->vars[ 5 ];
  child_state->vars[ 6 ] = state->vars[ 7 ];
  child_state->vars[ 7 ] = 0;
  child_state->vars[ 8 ] = state->vars[ 8 ];
  child_state->vars[ 9 ] = state->vars[ 9 ];
  child_state->vars[ 10 ] = state->vars[ 10 ];
  child_state->vars[ 11 ] = state->vars[ 11 ];
  child_state->vars[ 12 ] = state->vars[ 12 ];
  child_state->vars[ 13 ] = state->vars[ 13 ];
  child_state->vars[ 14 ] = state->vars[ 14 ];
  child_state->vars[ 15 ] = state->vars[ 15 ];
}

static void bwdrule13( const state_t *state, state_t *child_state )
{
  child_state->vars[ 0 ] = state->vars[ 0 ];
  child_state->vars[ 1 ] = state->vars[ 1 ];
  child_state->vars[ 2 ] = state->vars[ 2 ];
  child_state->vars[ 3 ] = state->vars[ 3 ];
  child_state->vars[ 4 ] = state->vars[ 4 ];
  child_state->vars[ 5 ] = state->vars[ 5 ];
  child_state->vars[ 6 ] = state->vars[ 6 ];
  child_state->vars[ 7 ] = state->vars[ 7 ];
  child_state->vars[ 8 ] = 0;
  child_state->vars[ 9 ] = state->vars[ 8 ];
  child_state->vars[ 10 ] = state->vars[ 10 ];
  child_state->vars[ 11 ] = state->vars[ 11 ];
  child_state->vars[ 12 ] = state->vars[ 12 ];
  child_state->vars[ 13 ] = state->vars[ 13 ];
  child_state->vars[ 14 ] = state->vars[ 14 ];
  child_state->vars[ 15 ] = state->vars[ 15 ];
}

static void bwdrule14( const state_t *state, state_t *child_state )
{
  child_state->vars[ 0 ] = state->vars[ 0 ];
  child_state->vars[ 1 ] = state->vars[ 1 ];
  child_state->vars[ 2 ] = state->vars[ 2 ];
  child_state->vars[ 3 ] = state->vars[ 3 ];
  child_state->vars[ 4 ] = state->vars[ 4 ];
  child_state->vars[ 5 ] = state->vars[ 5 ];
  child_state->vars[ 6 ] = state->vars[ 6 ];
  child_state->vars[ 7 ] = state->vars[ 7 ];
  child_state->vars[ 8 ] = state->vars[ 9 ];
  child_state->vars[ 9 ] = 0;
  child_state->vars[ 10 ] = state->vars[ 10 ];
  child_state->vars[ 11 ] = state->vars[ 11 ];
  child_state->vars[ 12 ] = state->vars[ 12 ];
  child_state->vars[ 13 ] = state->vars[ 13 ];
  child_state->vars[ 14 ] = state->vars[ 14 ];
  child_state->vars[ 15 ] = state->vars[ 15 ];
}

static void bwdrule15( const state_t *state, state_t *child_state )
{
  child_state->vars[ 0 ] = state->vars[ 0 ];
  child_state->vars[ 1 ] = state->vars[ 1 ];
  child_state->vars[ 2 ] = state->vars[ 2 ];
  child_state->vars[ 3 ] = state->vars[ 3 ];
  child_state->vars[ 4 ] = state->vars[ 4 ];
  child_state->vars[ 5 ] = state->vars[ 5 ];
  child_state->vars[ 6 ] = state->vars[ 6 ];
  child_state->vars[ 7 ] = state->vars[ 7 ];
  child_state->vars[ 8 ] = state->vars[ 8 ];
  child_state->vars[ 9 ] = 0;
  child_state->vars[ 10 ] = state->vars[ 9 ];
  child_state->vars[ 11 ] = state->vars[ 11 ];
  child_state->vars[ 12 ] = state->vars[ 12 ];
  child_state->vars[ 13 ] = state->vars[ 13 ];
  child_state->vars[ 14 ] = state->vars[ 14 ];
  child_state->vars[ 15 ] = state->vars[ 15 ];
}

static void bwdrule16( const state_t *state, state_t *child_state )
{
  child_state->vars[ 0 ] = state->vars[ 0 ];
  child_state->vars[ 1 ] = state->vars[ 1 ];
  child_state->vars[ 2 ] = state->vars[ 2 ];
  child_state->vars[ 3 ] = state->vars[ 3 ];
  child_state->vars[ 4 ] = state->vars[ 4 ];
  child_state->vars[ 5 ] = state->vars[ 5 ];
  child_state->vars[ 6 ] = state->vars[ 6 ];
  child_state->vars[ 7 ] = state->vars[ 7 ];
  child_state->vars[ 8 ] = state->vars[ 8 ];
  child_state->vars[ 9 ] = state->vars[ 10 ];
  child_state->vars[ 10 ] = 0;
  child_state->vars[ 11 ] = state->vars[ 11 ];
  child_state->vars[ 12 ] = state->vars[ 12 ];
  child_state->vars[ 13 ] = state->vars[ 13 ];
  child_state->vars[ 14 ] = state->vars[ 14 ];
  child_state->vars[ 15 ] = state->vars[ 15 ];
}

static void bwdrule17( const state_t *state, state_t *child_state )
{
  child_state->vars[ 0 ] = state->vars[ 0 ];
  child_state->vars[ 1 ] = state->vars[ 1 ];
  child_state->vars[ 2 ] = state->vars[ 2 ];
  child_state->vars[ 3 ] = state->vars[ 3 ];
  child_state->vars[ 4 ] = state->vars[ 4 ];
  child_state->vars[ 5 ] = state->vars[ 5 ];
  child_state->vars[ 6 ] = state->vars[ 6 ];
  child_state->vars[ 7 ] = state->vars[ 7 ];
  child_state->vars[ 8 ] = state->vars[ 8 ];
  child_state->vars[ 9 ] = state->vars[ 9 ];
  child_state->vars[ 10 ] = 0;
  child_state->vars[ 11 ] = state->vars[ 10 ];
  child_state->vars[ 12 ] = state->vars[ 12 ];
  child_state->vars[ 13 ] = state->vars[ 13 ];
  child_state->vars[ 14 ] = state->vars[ 14 ];
  child_state->vars[ 15 ] = state->vars[ 15 ];
}

static void bwdrule18( const state_t *state, state_t *child_state )
{
  child_state->vars[ 0 ] = state->vars[ 0 ];
  child_state->vars[ 1 ] = state->vars[ 1 ];
  child_state->vars[ 2 ] = state->vars[ 2 ];
  child_state->vars[ 3 ] = state->vars[ 3 ];
  child_state->vars[ 4 ] = state->vars[ 4 ];
  child_state->vars[ 5 ] = state->vars[ 5 ];
  child_state->vars[ 6 ] = state->vars[ 6 ];
  child_state->vars[ 7 ] = state->vars[ 7 ];
  child_state->vars[ 8 ] = state->vars[ 8 ];
  child_state->vars[ 9 ] = state->vars[ 9 ];
  child_state->vars[ 10 ] = state->vars[ 11 ];
  child_state->vars[ 11 ] = 0;
  child_state->vars[ 12 ] = state->vars[ 12 ];
  child_state->vars[ 13 ] = state->vars[ 13 ];
  child_state->vars[ 14 ] = state->vars[ 14 ];
  child_state->vars[ 15 ] = state->vars[ 15 ];
}

static void bwdrule19( const state_t *state, state_t *child_state )
{
  child_state->vars[ 0 ] = state->vars[ 0 ];
  child_state->vars[ 1 ] = state->vars[ 1 ];
  child_state->vars[ 2 ] = state->vars[ 2 ];
  child_state->vars[ 3 ] = state->vars[ 3 ];
  child_state->vars[ 4 ] = state->vars[ 4 ];
  child_state->vars[ 5 ] = state->vars[ 5 ];
  child_state->vars[ 6 ] = state->vars[ 6 ];
  child_state->vars[ 7 ] = state->vars[ 7 ];
  child_state->vars[ 8 ] = state->vars[ 8 ];
  child_state->vars[ 9 ] = state->vars[ 9 ];
  child_state->vars[ 10 ] = state->vars[ 10 ];
  child_state->vars[ 11 ] = state->vars[ 11 ];
  child_state->vars[ 12 ] = 0;
  child_state->vars[ 13 ] = state->vars[ 12 ];
  child_state->vars[ 14 ] = state->vars[ 14 ];
  child_state->vars[ 15 ] = state->vars[ 15 ];
}

static void bwdrule20( const state_t *state, state_t *child_state )
{
  child_state->vars[ 0 ] = state->vars[ 0 ];
  child_state->vars[ 1 ] = state->vars[ 1 ];
  child_state->vars[ 2 ] = state->vars[ 2 ];
  child_state->vars[ 3 ] = state->vars[ 3 ];
  child_state->vars[ 4 ] = state->vars[ 4 ];
  child_state->vars[ 5 ] = state->vars[ 5 ];
  child_state->vars[ 6 ] = state->vars[ 6 ];
  child_state->vars[ 7 ] = state->vars[ 7 ];
  child_state->vars[ 8 ] = state->vars[ 8 ];
  child_state->vars[ 9 ] = state->vars[ 9 ];
  child_state->vars[ 10 ] = state->vars[ 10 ];
  child_state->vars[ 11 ] = state->vars[ 11 ];
  child_state->vars[ 12 ] = state->vars[ 13 ];
  child_state->vars[ 13 ] = 0;
  child_state->vars[ 14 ] = state->vars[ 14 ];
  child_state->vars[ 15 ] = state->vars[ 15 ];
}

static void bwdrule21( const state_t *state, state_t *child_state )
{
  child_state->vars[ 0 ] = state->vars[ 0 ];
  child_state->vars[ 1 ] = state->vars[ 1 ];
  child_state->vars[ 2 ] = state->vars[ 2 ];
  child_state->vars[ 3 ] = state->vars[ 3 ];
  child_state->vars[ 4 ] = state->vars[ 4 ];
  child_state->vars[ 5 ] = state->vars[ 5 ];
  child_state->vars[ 6 ] = state->vars[ 6 ];
  child_state->vars[ 7 ] = state->vars[ 7 ];
  child_state->vars[ 8 ] = state->vars[ 8 ];
  child_state->vars[ 9 ] = state->vars[ 9 ];
  child_state->vars[ 10 ] = state->vars[ 10 ];
  child_state->vars[ 11 ] = state->vars[ 11 ];
  child_state->vars[ 12 ] = state->vars[ 12 ];
  child_state->vars[ 13 ] = 0;
  child_state->vars[ 14 ] = state->vars[ 13 ];
  child_state->vars[ 15 ] = state->vars[ 15 ];
}

static void bwdrule22( const state_t *state, state_t *child_state )
{
  child_state->vars[ 0 ] = state->vars[ 0 ];
  child_state->vars[ 1 ] = state->vars[ 1 ];
  child_state->vars[ 2 ] = state->vars[ 2 ];
  child_state->vars[ 3 ] = state->vars[ 3 ];
  child_state->vars[ 4 ] = state->vars[ 4 ];
  child_state->vars[ 5 ] = state->vars[ 5 ];
  child_state->vars[ 6 ] = state->vars[ 6 ];
  child_state->vars[ 7 ] = state->vars[ 7 ];
  child_state->vars[ 8 ] = state->vars[ 8 ];
  child_state->vars[ 9 ] = state->vars[ 9 ];
  child_state->vars[ 10 ] = state->vars[ 10 ];
  child_state->vars[ 11 ] = state->vars[ 11 ];
  child_state->vars[ 12 ] = state->vars[ 12 ];
  child_state->vars[ 13 ] = state->vars[ 14 ];
  child_state->vars[ 14 ] = 0;
  child_state->vars[ 15 ] = state->vars[ 15 ];
}

static void bwdrule23( const state_t *state, state_t *child_state )
{
  child_state->vars[ 0 ] = state->vars[ 0 ];
  child_state->vars[ 1 ] = state->vars[ 1 ];
  child_state->vars[ 2 ] = state->vars[ 2 ];
  child_state->vars[ 3 ] = state->vars[ 3 ];
  child_state->vars[ 4 ] = state->vars[ 4 ];
  child_state->vars[ 5 ] = state->vars[ 5 ];
  child_state->vars[ 6 ] = state->vars[ 6 ];
  child_state->vars[ 7 ] = state->vars[ 7 ];
  child_state->vars[ 8 ] = state->vars[ 8 ];
  child_state->vars[ 9 ] = state->vars[ 9 ];
  child_state->vars[ 10 ] = state->vars[ 10 ];
  child_state->vars[ 11 ] = state->vars[ 11 ];
  child_state->vars[ 12 ] = state->vars[ 12 ];
  child_state->vars[ 13 ] = state->vars[ 13 ];
  child_state->vars[ 14 ] = 0;
  child_state->vars[ 15 ] = state->vars[ 14 ];
}

static void bwdrule24( const state_t *state, state_t *child_state )
{
  child_state->vars[ 0 ] = state->vars[ 0 ];
  child_state->vars[ 1 ] = state->vars[ 1 ];
  child_state->vars[ 2 ] = state->vars[ 2 ];
  child_state->vars[ 3 ] = state->vars[ 3 ];
  child_state->vars[ 4 ] = state->vars[ 4 ];
  child_state->vars[ 5 ] = state->vars[ 5 ];
  child_state->vars[ 6 ] = state->vars[ 6 ];
  child_state->vars[ 7 ] = state->vars[ 7 ];
  child_state->vars[ 8 ] = state->vars[ 8 ];
  child_state->vars[ 9 ] = state->vars[ 9 ];
  child_state->vars[ 10 ] = state->vars[ 10 ];
  child_state->vars[ 11 ] = state->vars[ 11 ];
  child_state->vars[ 12 ] = state->vars[ 12 ];
  child_state->vars[ 13 ] = state->vars[ 13 ];
  child_state->vars[ 14 ] = state->vars[ 15 ];
  child_state->vars[ 15 ] = 0;
}

static void bwdrule25( const state_t *state, state_t *child_state )
{
  child_state->vars[ 0 ] = 0;
  child_state->vars[ 1 ] = state->vars[ 1 ];
  child_state->vars[ 2 ] = state->vars[ 2 ];
  child_state->vars[ 3 ] = state->vars[ 3 ];
  child_state->vars[ 4 ] = state->vars[ 0 ];
  child_state->vars[ 5 ] = state->vars[ 5 ];
  child_state->vars[ 6 ] = state->vars[ 6 ];
  child_state->vars[ 7 ] = state->vars[ 7 ];
  child_state->vars[ 8 ] = state->vars[ 8 ];
  child_state->vars[ 9 ] = state->vars[ 9 ];
  child_state->vars[ 10 ] = state->vars[ 10 ];
  child_state->vars[ 11 ] = state->vars[ 11 ];
  child_state->vars[ 12 ] = state->vars[ 12 ];
  child_state->vars[ 13 ] = state->vars[ 13 ];
  child_state->vars[ 14 ] = state->vars[ 14 ];
  child_state->vars[ 15 ] = state->vars[ 15 ];
}

static void bwdrule26( const state_t *state, state_t *child_state )
{
  child_state->vars[ 0 ] = state->vars[ 4 ];
  child_state->vars[ 1 ] = state->vars[ 1 ];
  child_state->vars[ 2 ] = state->vars[ 2 ];
  child_state->vars[ 3 ] = state->vars[ 3 ];
  child_state->vars[ 4 ] = 0;
  child_state->vars[ 5 ] = state->vars[ 5 ];
  child_state->vars[ 6 ] = state->vars[ 6 ];
  child_state->vars[ 7 ] = state->vars[ 7 ];
  child_state->vars[ 8 ] = state->vars[ 8 ];
  child_state->vars[ 9 ] = state->vars[ 9 ];
  child_state->vars[ 10 ] = state->vars[ 10 ];
  child_state->vars[ 11 ] = state->vars[ 11 ];
  child_state->vars[ 12 ] = state->vars[ 12 ];
  child_state->vars[ 13 ] = state->vars[ 13 ];
  child_state->vars[ 14 ] = state->vars[ 14 ];
  child_state->vars[ 15 ] = state->vars[ 15 ];
}

static void bwdrule27( const state_t *state, state_t *child_state )
{
  child_state->vars[ 0 ] = state->vars[ 0 ];
  child_state->vars[ 1 ] = 0;
  child_state->vars[ 2 ] = state->vars[ 2 ];
  child_state->vars[ 3 ] = state->vars[ 3 ];
  child_state->vars[ 4 ] = state->vars[ 4 ];
  child_state->vars[ 5 ] = state->vars[ 1 ];
  child_state->vars[ 6 ] = state->vars[ 6 ];
  child_state->vars[ 7 ] = state->vars[ 7 ];
  child_state->vars[ 8 ] = state->vars[ 8 ];
  child_state->vars[ 9 ] = state->vars[ 9 ];
  child_state->vars[ 10 ] = state->vars[ 10 ];
  child_state->vars[ 11 ] = state->vars[ 11 ];
  child_state->vars[ 12 ] = state->vars[ 12 ];
  child_state->vars[ 13 ] = state->vars[ 13 ];
  child_state->vars[ 14 ] = state->vars[ 14 ];
  child_state->vars[ 15 ] = state->vars[ 15 ];
}

static void bwdrule28( const state_t *state, state_t *child_state )
{
  child_state->vars[ 0 ] = state->vars[ 0 ];
  child_state->vars[ 1 ] = state->vars[ 5 ];
  child_state->vars[ 2 ] = state->vars[ 2 ];
  child_state->vars[ 3 ] = state->vars[ 3 ];
  child_state->vars[ 4 ] = state->vars[ 4 ];
  child_state->vars[ 5 ] = 0;
  child_state->vars[ 6 ] = state->vars[ 6 ];
  child_state->vars[ 7 ] = state->vars[ 7 ];
  child_state->vars[ 8 ] = state->vars[ 8 ];
  child_state->vars[ 9 ] = state->vars[ 9 ];
  child_state->vars[ 10 ] = state->vars[ 10 ];
  child_state->vars[ 11 ] = state->vars[ 11 ];
  child_state->vars[ 12 ] = state->vars[ 12 ];
  child_state->vars[ 13 ] = state->vars[ 13 ];
  child_state->vars[ 14 ] = state->vars[ 14 ];
  child_state->vars[ 15 ] = state->vars[ 15 ];
}

static void bwdrule29( const state_t *state, state_t *child_state )
{
  child_state->vars[ 0 ] = state->vars[ 0 ];
  child_state->vars[ 1 ] = state->vars[ 1 ];
  child_state->vars[ 2 ] = 0;
  child_state->vars[ 3 ] = state->vars[ 3 ];
  child_state->vars[ 4 ] = state->vars[ 4 ];
  child_state->vars[ 5 ] = state->vars[ 5 ];
  child_state->vars[ 6 ] = state->vars[ 2 ];
  child_state->vars[ 7 ] = state->vars[ 7 ];
  child_state->vars[ 8 ] = state->vars[ 8 ];
  child_state->vars[ 9 ] = state->vars[ 9 ];
  child_state->vars[ 10 ] = state->vars[ 10 ];
  child_state->vars[ 11 ] = state->vars[ 11 ];
  child_state->vars[ 12 ] = state->vars[ 12 ];
  child_state->vars[ 13 ] = state->vars[ 13 ];
  child_state->vars[ 14 ] = state->vars[ 14 ];
  child_state->vars[ 15 ] = state->vars[ 15 ];
}

static void bwdrule30( const state_t *state, state_t *child_state )
{
  child_state->vars[ 0 ] = state->vars[ 0 ];
  child_state->vars[ 1 ] = state->vars[ 1 ];
  child_state->vars[ 2 ] = state->vars[ 6 ];
  child_state->vars[ 3 ] = state->vars[ 3 ];
  child_state->vars[ 4 ] = state->vars[ 4 ];
  child_state->vars[ 5 ] = state->vars[ 5 ];
  child_state->vars[ 6 ] = 0;
  child_state->vars[ 7 ] = state->vars[ 7 ];
  child_state->vars[ 8 ] = state->vars[ 8 ];
  child_state->vars[ 9 ] = state->vars[ 9 ];
  child_state->vars[ 10 ] = state->vars[ 10 ];
  child_state->vars[ 11 ] = state->vars[ 11 ];
  child_state->vars[ 12 ] = state->vars[ 12 ];
  child_state->vars[ 13 ] = state->vars[ 13 ];
  child_state->vars[ 14 ] = state->vars[ 14 ];
  child_state->vars[ 15 ] = state->vars[ 15 ];
}

static void bwdrule31( const state_t *state, state_t *child_state )
{
  child_state->vars[ 0 ] = state->vars[ 0 ];
  child_state->vars[ 1 ] = state->vars[ 1 ];
  child_state->vars[ 2 ] = state->vars[ 2 ];
  child_state->vars[ 3 ] = 0;
  child_state->vars[ 4 ] = state->vars[ 4 ];
  child_state->vars[ 5 ] = state->vars[ 5 ];
  child_state->vars[ 6 ] = state->vars[ 6 ];
  child_state->vars[ 7 ] = state->vars[ 3 ];
  child_state->vars[ 8 ] = state->vars[ 8 ];
  child_state->vars[ 9 ] = state->vars[ 9 ];
  child_state->vars[ 10 ] = state->vars[ 10 ];
  child_state->vars[ 11 ] = state->vars[ 11 ];
  child_state->vars[ 12 ] = state->vars[ 12 ];
  child_state->vars[ 13 ] = state->vars[ 13 ];
  child_state->vars[ 14 ] = state->vars[ 14 ];
  child_state->vars[ 15 ] = state->vars[ 15 ];
}

static void bwdrule32( const state_t *state, state_t *child_state )
{
  child_state->vars[ 0 ] = state->vars[ 0 ];
  child_state->vars[ 1 ] = state->vars[ 1 ];
  child_state->vars[ 2 ] = state->vars[ 2 ];
  child_state->vars[ 3 ] = state->vars[ 7 ];
  child_state->vars[ 4 ] = state->vars[ 4 ];
  child_state->vars[ 5 ] = state->vars[ 5 ];
  child_state->vars[ 6 ] = state->vars[ 6 ];
  child_state->vars[ 7 ] = 0;
  child_state->vars[ 8 ] = state->vars[ 8 ];
  child_state->vars[ 9 ] = state->vars[ 9 ];
  child_state->vars[ 10 ] = state->vars[ 10 ];
  child_state->vars[ 11 ] = state->vars[ 11 ];
  child_state->vars[ 12 ] = state->vars[ 12 ];
  child_state->vars[ 13 ] = state->vars[ 13 ];
  child_state->vars[ 14 ] = state->vars[ 14 ];
  child_state->vars[ 15 ] = state->vars[ 15 ];
}

static void bwdrule33( const state_t *state, state_t *child_state )
{
  child_state->vars[ 0 ] = state->vars[ 0 ];
  child_state->vars[ 1 ] = state->vars[ 1 ];
  child_state->vars[ 2 ] = state->vars[ 2 ];
  child_state->vars[ 3 ] = state->vars[ 3 ];
  child_state->vars[ 4 ] = 0;
  child_state->vars[ 5 ] = state->vars[ 5 ];
  child_state->vars[ 6 ] = state->vars[ 6 ];
  child_state->vars[ 7 ] = state->vars[ 7 ];
  child_state->vars[ 8 ] = state->vars[ 4 ];
  child_state->vars[ 9 ] = state->vars[ 9 ];
  child_state->vars[ 10 ] = state->vars[ 10 ];
  child_state->vars[ 11 ] = state->vars[ 11 ];
  child_state->vars[ 12 ] = state->vars[ 12 ];
  child_state->vars[ 13 ] = state->vars[ 13 ];
  child_state->vars[ 14 ] = state->vars[ 14 ];
  child_state->vars[ 15 ] = state->vars[ 15 ];
}

static void bwdrule34( const state_t *state, state_t *child_state )
{
  child_state->vars[ 0 ] = state->vars[ 0 ];
  child_state->vars[ 1 ] = state->vars[ 1 ];
  child_state->vars[ 2 ] = state->vars[ 2 ];
  child_state->vars[ 3 ] = state->vars[ 3 ];
  child_state->vars[ 4 ] = state->vars[ 8 ];
  child_state->vars[ 5 ] = state->vars[ 5 ];
  child_state->vars[ 6 ] = state->vars[ 6 ];
  child_state->vars[ 7 ] = state->vars[ 7 ];
  child_state->vars[ 8 ] = 0;
  child_state->vars[ 9 ] = state->vars[ 9 ];
  child_state->vars[ 10 ] = state->vars[ 10 ];
  child_state->vars[ 11 ] = state->vars[ 11 ];
  child_state->vars[ 12 ] = state->vars[ 12 ];
  child_state->vars[ 13 ] = state->vars[ 13 ];
  child_state->vars[ 14 ] = state->vars[ 14 ];
  child_state->vars[ 15 ] = state->vars[ 15 ];
}

static void bwdrule35( const state_t *state, state_t *child_state )
{
  child_state->vars[ 0 ] = state->vars[ 0 ];
  child_state->vars[ 1 ] = state->vars[ 1 ];
  child_state->vars[ 2 ] = state->vars[ 2 ];
  child_state->vars[ 3 ] = state->vars[ 3 ];
  child_state->vars[ 4 ] = state->vars[ 4 ];
  child_state->vars[ 5 ] = 0;
  child_state->vars[ 6 ] = state->vars[ 6 ];
  child_state->vars[ 7 ] = state->vars[ 7 ];
  child_state->vars[ 8 ] = state->vars[ 8 ];
  child_state->vars[ 9 ] = state->vars[ 5 ];
  child_state->vars[ 10 ] = state->vars[ 10 ];
  child_state->vars[ 11 ] = state->vars[ 11 ];
  child_state->vars[ 12 ] = state->vars[ 12 ];
  child_state->vars[ 13 ] = state->vars[ 13 ];
  child_state->vars[ 14 ] = state->vars[ 14 ];
  child_state->vars[ 15 ] = state->vars[ 15 ];
}

static void bwdrule36( const state_t *state, state_t *child_state )
{
  child_state->vars[ 0 ] = state->vars[ 0 ];
  child_state->vars[ 1 ] = state->vars[ 1 ];
  child_state->vars[ 2 ] = state->vars[ 2 ];
  child_state->vars[ 3 ] = state->vars[ 3 ];
  child_state->vars[ 4 ] = state->vars[ 4 ];
  child_state->vars[ 5 ] = state->vars[ 9 ];
  child_state->vars[ 6 ] = state->vars[ 6 ];
  child_state->vars[ 7 ] = state->vars[ 7 ];
  child_state->vars[ 8 ] = state->vars[ 8 ];
  child_state->vars[ 9 ] = 0;
  child_state->vars[ 10 ] = state->vars[ 10 ];
  child_state->vars[ 11 ] = state->vars[ 11 ];
  child_state->vars[ 12 ] = state->vars[ 12 ];
  child_state->vars[ 13 ] = state->vars[ 13 ];
  child_state->vars[ 14 ] = state->vars[ 14 ];
  child_state->vars[ 15 ] = state->vars[ 15 ];
}

static void bwdrule37( const state_t *state, state_t *child_state )
{
  child_state->vars[ 0 ] = state->vars[ 0 ];
  child_state->vars[ 1 ] = state->vars[ 1 ];
  child_state->vars[ 2 ] = state->vars[ 2 ];
  child_state->vars[ 3 ] = state->vars[ 3 ];
  child_state->vars[ 4 ] = state->vars[ 4 ];
  child_state->vars[ 5 ] = state->vars[ 5 ];
  child_state->vars[ 6 ] = 0;
  child_state->vars[ 7 ] = state->vars[ 7 ];
  child_state->vars[ 8 ] = state->vars[ 8 ];
  child_state->vars[ 9 ] = state->vars[ 9 ];
  child_state->vars[ 10 ] = state->vars[ 6 ];
  child_state->vars[ 11 ] = state->vars[ 11 ];
  child_state->vars[ 12 ] = state->vars[ 12 ];
  child_state->vars[ 13 ] = state->vars[ 13 ];
  child_state->vars[ 14 ] = state->vars[ 14 ];
  child_state->vars[ 15 ] = state->vars[ 15 ];
}

static void bwdrule38( const state_t *state, state_t *child_state )
{
  child_state->vars[ 0 ] = state->vars[ 0 ];
  child_state->vars[ 1 ] = state->vars[ 1 ];
  child_state->vars[ 2 ] = state->vars[ 2 ];
  child_state->vars[ 3 ] = state->vars[ 3 ];
  child_state->vars[ 4 ] = state->vars[ 4 ];
  child_state->vars[ 5 ] = state->vars[ 5 ];
  child_state->vars[ 6 ] = state->vars[ 10 ];
  child_state->vars[ 7 ] = state->vars[ 7 ];
  child_state->vars[ 8 ] = state->vars[ 8 ];
  child_state->vars[ 9 ] = state->vars[ 9 ];
  child_state->vars[ 10 ] = 0;
  child_state->vars[ 11 ] = state->vars[ 11 ];
  child_state->vars[ 12 ] = state->vars[ 12 ];
  child_state->vars[ 13 ] = state->vars[ 13 ];
  child_state->vars[ 14 ] = state->vars[ 14 ];
  child_state->vars[ 15 ] = state->vars[ 15 ];
}

static void bwdrule39( const state_t *state, state_t *child_state )
{
  child_state->vars[ 0 ] = state->vars[ 0 ];
  child_state->vars[ 1 ] = state->vars[ 1 ];
  child_state->vars[ 2 ] = state->vars[ 2 ];
  child_state->vars[ 3 ] = state->vars[ 3 ];
  child_state->vars[ 4 ] = state->vars[ 4 ];
  child_state->vars[ 5 ] = state->vars[ 5 ];
  child_state->vars[ 6 ] = state->vars[ 6 ];
  child_state->vars[ 7 ] = 0;
  child_state->vars[ 8 ] = state->vars[ 8 ];
  child_state->vars[ 9 ] = state->vars[ 9 ];
  child_state->vars[ 10 ] = state->vars[ 10 ];
  child_state->vars[ 11 ] = state->vars[ 7 ];
  child_state->vars[ 12 ] = state->vars[ 12 ];
  child_state->vars[ 13 ] = state->vars[ 13 ];
  child_state->vars[ 14 ] = state->vars[ 14 ];
  child_state->vars[ 15 ] = state->vars[ 15 ];
}

static void bwdrule40( const state_t *state, state_t *child_state )
{
  child_state->vars[ 0 ] = state->vars[ 0 ];
  child_state->vars[ 1 ] = state->vars[ 1 ];
  child_state->vars[ 2 ] = state->vars[ 2 ];
  child_state->vars[ 3 ] = state->vars[ 3 ];
  child_state->vars[ 4 ] = state->vars[ 4 ];
  child_state->vars[ 5 ] = state->vars[ 5 ];
  child_state->vars[ 6 ] = state->vars[ 6 ];
  child_state->vars[ 7 ] = state->vars[ 11 ];
  child_state->vars[ 8 ] = state->vars[ 8 ];
  child_state->vars[ 9 ] = state->vars[ 9 ];
  child_state->vars[ 10 ] = state->vars[ 10 ];
  child_state->vars[ 11 ] = 0;
  child_state->vars[ 12 ] = state->vars[ 12 ];
  child_state->vars[ 13 ] = state->vars[ 13 ];
  child_state->vars[ 14 ] = state->vars[ 14 ];
  child_state->vars[ 15 ] = state->vars[ 15 ];
}

static void bwdrule41( const state_t *state, state_t *child_state )
{
  child_state->vars[ 0 ] = state->vars[ 0 ];
  child_state->vars[ 1 ] = state->vars[ 1 ];
  child_state->vars[ 2 ] = state->vars[ 2 ];
  child_state->vars[ 3 ] = state->vars[ 3 ];
  child_state->vars[ 4 ] = state->vars[ 4 ];
  child_state->vars[ 5 ] = state->vars[ 5 ];
  child_state->vars[ 6 ] = state->vars[ 6 ];
  child_state->vars[ 7 ] = state->vars[ 7 ];
  child_state->vars[ 8 ] = 0;
  child_state->vars[ 9 ] = state->vars[ 9 ];
  child_state->vars[ 10 ] = state->vars[ 10 ];
  child_state->vars[ 11 ] = state->vars[ 11 ];
  child_state->vars[ 12 ] = state->vars[ 8 ];
  child_state->vars[ 13 ] = state->vars[ 13 ];
  child_state->vars[ 14 ] = state->vars[ 14 ];
  child_state->vars[ 15 ] = state->vars[ 15 ];
}

static void bwdrule42( const state_t *state, state_t *child_state )
{
  child_state->vars[ 0 ] = state->vars[ 0 ];
  child_state->vars[ 1 ] = state->vars[ 1 ];
  child_state->vars[ 2 ] = state->vars[ 2 ];
  child_state->vars[ 3 ] = state->vars[ 3 ];
  child_state->vars[ 4 ] = state->vars[ 4 ];
  child_state->vars[ 5 ] = state->vars[ 5 ];
  child_state->vars[ 6 ] = state->vars[ 6 ];
  child_state->vars[ 7 ] = state->vars[ 7 ];
  child_state->vars[ 8 ] = state->vars[ 12 ];
  child_state->vars[ 9 ] = state->vars[ 9 ];
  child_state->vars[ 10 ] = state->vars[ 10 ];
  child_state->vars[ 11 ] = state->vars[ 11 ];
  child_state->vars[ 12 ] = 0;
  child_state->vars[ 13 ] = state->vars[ 13 ];
  child_state->vars[ 14 ] = state->vars[ 14 ];
  child_state->vars[ 15 ] = state->vars[ 15 ];
}

static void bwdrule43( const state_t *state, state_t *child_state )
{
  child_state->vars[ 0 ] = state->vars[ 0 ];
  child_state->vars[ 1 ] = state->vars[ 1 ];
  child_state->vars[ 2 ] = state->vars[ 2 ];
  child_state->vars[ 3 ] = state->vars[ 3 ];
  child_state->vars[ 4 ] = state->vars[ 4 ];
  child_state->vars[ 5 ] = state->vars[ 5 ];
  child_state->vars[ 6 ] = state->vars[ 6 ];
  child_state->vars[ 7 ] = state->vars[ 7 ];
  child_state->vars[ 8 ] = state->vars[ 8 ];
  child_state->vars[ 9 ] = 0;
  child_state->vars[ 10 ] = state->vars[ 10 ];
  child_state->vars[ 11 ] = state->vars[ 11 ];
  child_state->vars[ 12 ] = state->vars[ 12 ];
  child_state->vars[ 13 ] = state->vars[ 9 ];
  child_state->vars[ 14 ] = state->vars[ 14 ];
  child_state->vars[ 15 ] = state->vars[ 15 ];
}

static void bwdrule44( const state_t *state, state_t *child_state )
{
  child_state->vars[ 0 ] = state->vars[ 0 ];
  child_state->vars[ 1 ] = state->vars[ 1 ];
  child_state->vars[ 2 ] = state->vars[ 2 ];
  child_state->vars[ 3 ] = state->vars[ 3 ];
  child_state->vars[ 4 ] = state->vars[ 4 ];
  child_state->vars[ 5 ] = state->vars[ 5 ];
  child_state->vars[ 6 ] = state->vars[ 6 ];
  child_state->vars[ 7 ] = state->vars[ 7 ];
  child_state->vars[ 8 ] = state->vars[ 8 ];
  child_state->vars[ 9 ] = state->vars[ 13 ];
  child_state->vars[ 10 ] = state->vars[ 10 ];
  child_state->vars[ 11 ] = state->vars[ 11 ];
  child_state->vars[ 12 ] = state->vars[ 12 ];
  child_state->vars[ 13 ] = 0;
  child_state->vars[ 14 ] = state->vars[ 14 ];
  child_state->vars[ 15 ] = state->vars[ 15 ];
}

static void bwdrule45( const state_t *state, state_t *child_state )
{
  child_state->vars[ 0 ] = state->vars[ 0 ];
  child_state->vars[ 1 ] = state->vars[ 1 ];
  child_state->vars[ 2 ] = state->vars[ 2 ];
  child_state->vars[ 3 ] = state->vars[ 3 ];
  child_state->vars[ 4 ] = state->vars[ 4 ];
  child_state->vars[ 5 ] = state->vars[ 5 ];
  child_state->vars[ 6 ] = state->vars[ 6 ];
  child_state->vars[ 7 ] = state->vars[ 7 ];
  child_state->vars[ 8 ] = state->vars[ 8 ];
  child_state->vars[ 9 ] = state->vars[ 9 ];
  child_state->vars[ 10 ] = 0;
  child_state->vars[ 11 ] = state->vars[ 11 ];
  child_state->vars[ 12 ] = state->vars[ 12 ];
  child_state->vars[ 13 ] = state->vars[ 13 ];
  child_state->vars[ 14 ] = state->vars[ 10 ];
  child_state->vars[ 15 ] = state->vars[ 15 ];
}

static void bwdrule46( const state_t *state, state_t *child_state )
{
  child_state->vars[ 0 ] = state->vars[ 0 ];
  child_state->vars[ 1 ] = state->vars[ 1 ];
  child_state->vars[ 2 ] = state->vars[ 2 ];
  child_state->vars[ 3 ] = state->vars[ 3 ];
  child_state->vars[ 4 ] = state->vars[ 4 ];
  child_state->vars[ 5 ] = state->vars[ 5 ];
  child_state->vars[ 6 ] = state->vars[ 6 ];
  child_state->vars[ 7 ] = state->vars[ 7 ];
  child_state->vars[ 8 ] = state->vars[ 8 ];
  child_state->vars[ 9 ] = state->vars[ 9 ];
  child_state->vars[ 10 ] = state->vars[ 14 ];
  child_state->vars[ 11 ] = state->vars[ 11 ];
  child_state->vars[ 12 ] = state->vars[ 12 ];
  child_state->vars[ 13 ] = state->vars[ 13 ];
  child_state->vars[ 14 ] = 0;
  child_state->vars[ 15 ] = state->vars[ 15 ];
}

static void bwdrule47( const state_t *state, state_t *child_state )
{
  child_state->vars[ 0 ] = state->vars[ 0 ];
  child_state->vars[ 1 ] = state->vars[ 1 ];
  child_state->vars[ 2 ] = state->vars[ 2 ];
  child_state->vars[ 3 ] = state->vars[ 3 ];
  child_state->vars[ 4 ] = state->vars[ 4 ];
  child_state->vars[ 5 ] = state->vars[ 5 ];
  child_state->vars[ 6 ] = state->vars[ 6 ];
  child_state->vars[ 7 ] = state->vars[ 7 ];
  child_state->vars[ 8 ] = state->vars[ 8 ];
  child_state->vars[ 9 ] = state->vars[ 9 ];
  child_state->vars[ 10 ] = state->vars[ 10 ];
  child_state->vars[ 11 ] = 0;
  child_state->vars[ 12 ] = state->vars[ 12 ];
  child_state->vars[ 13 ] = state->vars[ 13 ];
  child_state->vars[ 14 ] = state->vars[ 14 ];
  child_state->vars[ 15 ] = state->vars[ 11 ];
}

static void bwdrule48( const state_t *state, state_t *child_state )
{
  child_state->vars[ 0 ] = state->vars[ 0 ];
  child_state->vars[ 1 ] = state->vars[ 1 ];
  child_state->vars[ 2 ] = state->vars[ 2 ];
  child_state->vars[ 3 ] = state->vars[ 3 ];
  child_state->vars[ 4 ] = state->vars[ 4 ];
  child_state->vars[ 5 ] = state->vars[ 5 ];
  child_state->vars[ 6 ] = state->vars[ 6 ];
  child_state->vars[ 7 ] = state->vars[ 7 ];
  child_state->vars[ 8 ] = state->vars[ 8 ];
  child_state->vars[ 9 ] = state->vars[ 9 ];
  child_state->vars[ 10 ] = state->vars[ 10 ];
  child_state->vars[ 11 ] = state->vars[ 15 ];
  child_state->vars[ 12 ] = state->vars[ 12 ];
  child_state->vars[ 13 ] = state->vars[ 13 ];
  child_state->vars[ 14 ] = state->vars[ 14 ];
  child_state->vars[ 15 ] = 0;
}

static actfuncptr bwd_rules[ 48 ] = { bwdrule1, bwdrule2, bwdrule3, bwdrule4, bwdrule5, bwdrule6, bwdrule7, bwdrule8, bwdrule9, bwdrule10, bwdrule11, bwdrule12, bwdrule13, bwdrule14, bwdrule15, bwdrule16, bwdrule17, bwdrule18, bwdrule19, bwdrule20, bwdrule21, bwdrule22, bwdrule23, bwdrule24, bwdrule25, bwdrule26, bwdrule27, bwdrule28, bwdrule29, bwdrule30, bwdrule31, bwdrule32, bwdrule33, bwdrule34, bwdrule35, bwdrule36, bwdrule37, bwdrule38, bwdrule39, bwdrule40, bwdrule41, bwdrule42, bwdrule43, bwdrule44, bwdrule45, bwdrule46, bwdrule47, bwdrule48 };

static int bwdfn15_a0_3( const state_t *state, void *next_func )
{
  *((funcptr *)next_func) = NULL;
  return 45;
}

static int bwdfn15_a0_2( const state_t *state, void *next_func )
{
  *((funcptr *)next_func) = bwdfn15_a0_3;
  return 36;
}

static int bwdfn15_a0_1( const state_t *state, void *next_func )
{
  *((funcptr *)next_func) = bwdfn15_a0_2;
  return 17;
}

static int bwdfn15( const state_t *state, void *next_func )
{
  if( state->vars[ 10 ] == 0 ) {
    *((funcptr *)next_func) = bwdfn15_a0_1;
    return 14;
  } else {
    return -1;
  }
}

static int bwdfn14_a0_3( const state_t *state, void *next_func )
{
  *((funcptr *)next_func) = bwdfn15;
  return 43;
}

static int bwdfn14_a0_2( const state_t *state, void *next_func )
{
  *((funcptr *)next_func) = bwdfn14_a0_3;
  return 34;
}

static int bwdfn14_a0_1( const state_t *state, void *next_func )
{
  *((funcptr *)next_func) = bwdfn14_a0_2;
  return 15;
}

static int bwdfn14( const state_t *state, void *next_func )
{
  if( state->vars[ 9 ] == 0 ) {
    *((funcptr *)next_func) = bwdfn14_a0_1;
    return 12;
  } else {
    return bwdfn15( state, next_func );
  }
}

static int bwdfn13_a0_3( const state_t *state, void *next_func )
{
  *((funcptr *)next_func) = bwdfn14;
  return 37;
}

static int bwdfn13_a0_2( const state_t *state, void *next_func )
{
  *((funcptr *)next_func) = bwdfn13_a0_3;
  return 28;
}

static int bwdfn13_a0_1( const state_t *state, void *next_func )
{
  *((funcptr *)next_func) = bwdfn13_a0_2;
  return 11;
}

static int bwdfn13( const state_t *state, void *next_func )
{
  if( state->vars[ 6 ] == 0 ) {
    *((funcptr *)next_func) = bwdfn13_a0_1;
    return 8;
  } else {
    return bwdfn14( state, next_func );
  }
}

static int bwdfn12_a0_3( const state_t *state, void *next_func )
{
  *((funcptr *)next_func) = bwdfn13;
  return 35;
}

static int bwdfn12_a0_2( const state_t *state, void *next_func )
{
  *((funcptr *)next_func) = bwdfn12_a0_3;
  return 26;
}

static int bwdfn12_a0_1( const state_t *state, void *next_func )
{
  *((funcptr *)next_func) = bwdfn12_a0_2;
  return 9;
}

static int bwdfn12( const state_t *state, void *next_func )
{
  if( state->vars[ 5 ] == 0 ) {
    *((funcptr *)next_func) = bwdfn12_a0_1;
    return 6;
  } else {
    return bwdfn13( state, next_func );
  }
}

static int bwdfn11_a0_2( const state_t *state, void *next_func )
{
  *((funcptr *)next_func) = bwdfn12;
  return 44;
}

static int bwdfn11_a0_1( const state_t *state, void *next_func )
{
  *((funcptr *)next_func) = bwdfn11_a0_2;
  return 23;
}

static int bwdfn11( const state_t *state, void *next_func )
{
  if( state->vars[ 14 ] == 0 ) {
    *((funcptr *)next_func) = bwdfn11_a0_1;
    return 20;
  } else {
    return bwdfn12( state, next_func );
  }
}

static int bwdfn10_a0_2( const state_t *state, void *next_func )
{
  *((funcptr *)next_func) = bwdfn11;
  return 42;
}

static int bwdfn10_a0_1( const state_t *state, void *next_func )
{
  *((funcptr *)next_func) = bwdfn10_a0_2;
  return 21;
}

static int bwdfn10( const state_t *state, void *next_func )
{
  if( state->vars[ 13 ] == 0 ) {
    *((funcptr *)next_func) = bwdfn10_a0_1;
    return 18;
  } else {
    return bwdfn11( state, next_func );
  }
}

static int bwdfn9_a0_2( const state_t *state, void *next_func )
{
  *((funcptr *)next_func) = bwdfn10;
  return 47;
}

static int bwdfn9_a0_1( const state_t *state, void *next_func )
{
  *((funcptr *)next_func) = bwdfn9_a0_2;
  return 38;
}

static int bwdfn9( const state_t *state, void *next_func )
{
  if( state->vars[ 11 ] == 0 ) {
    *((funcptr *)next_func) = bwdfn9_a0_1;
    return 16;
  } else {
    return bwdfn10( state, next_func );
  }
}

static int bwdfn8_a0_2( const state_t *state, void *next_func )
{
  *((funcptr *)next_func) = bwdfn9;
  return 41;
}

static int bwdfn8_a0_1( const state_t *state, void *next_func )
{
  *((funcptr *)next_func) = bwdfn8_a0_2;
  return 32;
}

static int bwdfn8( const state_t *state, void *next_func )
{
  if( state->vars[ 8 ] == 0 ) {
    *((funcptr *)next_func) = bwdfn8_a0_1;
    return 13;
  } else {
    return bwdfn9( state, next_func );
  }
}

static int bwdfn7_a0_2( const state_t *state, void *next_func )
{
  *((funcptr *)next_func) = bwdfn8;
  return 39;
}

static int bwdfn7_a0_1( const state_t *state, void *next_func )
{
  *((funcptr *)next_func) = bwdfn7_a0_2;
  return 30;
}

static int bwdfn7( const state_t *state, void *next_func )
{
  if( state->vars[ 7 ] == 0 ) {
    *((funcptr *)next_func) = bwdfn7_a0_1;
    return 10;
  } else {
    return bwdfn8( state, next_func );
  }
}

static int bwdfn6_a0_2( const state_t *state, void *next_func )
{
  *((funcptr *)next_func) = bwdfn7;
  return 33;
}

static int bwdfn6_a0_1( const state_t *state, void *next_func )
{
  *((funcptr *)next_func) = bwdfn6_a0_2;
  return 24;
}

static int bwdfn6( const state_t *state, void *next_func )
{
  if( state->vars[ 4 ] == 0 ) {
    *((funcptr *)next_func) = bwdfn6_a0_1;
    return 7;
  } else {
    return bwdfn7( state, next_func );
  }
}

static int bwdfn5_a0_2( const state_t *state, void *next_func )
{
  *((funcptr *)next_func) = bwdfn6;
  return 29;
}

static int bwdfn5_a0_1( const state_t *state, void *next_func )
{
  *((funcptr *)next_func) = bwdfn5_a0_2;
  return 5;
}

static int bwdfn5( const state_t *state, void *next_func )
{
  if( state->vars[ 2 ] == 0 ) {
    *((funcptr *)next_func) = bwdfn5_a0_1;
    return 2;
  } else {
    return bwdfn6( state, next_func );
  }
}

static int bwdfn4_a0_2( const state_t *state, void *next_func )
{
  *((funcptr *)next_func) = bwdfn5;
  return 27;
}

static int bwdfn4_a0_1( const state_t *state, void *next_func )
{
  *((funcptr *)next_func) = bwdfn4_a0_2;
  return 3;
}

static int bwdfn4( const state_t *state, void *next_func )
{
  if( state->vars[ 1 ] == 0 ) {
    *((funcptr *)next_func) = bwdfn4_a0_1;
    return 0;
  } else {
    return bwdfn5( state, next_func );
  }
}

static int bwdfn3_a0_1( const state_t *state, void *next_func )
{
  *((funcptr *)next_func) = bwdfn4;
  return 46;
}

static int bwdfn3( const state_t *state, void *next_func )
{
  if( state->vars[ 15 ] == 0 ) {
    *((funcptr *)next_func) = bwdfn3_a0_1;
    return 22;
  } else {
    return bwdfn4( state, next_func );
  }
}

static int bwdfn2_a0_1( const state_t *state, void *next_func )
{
  *((funcptr *)next_func) = bwdfn3;
  return 40;
}

static int bwdfn2( const state_t *state, void *next_func )
{
  if( state->vars[ 12 ] == 0 ) {
    *((funcptr *)next_func) = bwdfn2_a0_1;
    return 19;
  } else {
    return bwdfn3( state, next_func );
  }
}

static int bwdfn1_a0_1( const state_t *state, void *next_func )
{
  *((funcptr *)next_func) = bwdfn2;
  return 31;
}

static int bwdfn1( const state_t *state, void *next_func )
{
  if( state->vars[ 3 ] == 0 ) {
    *((funcptr *)next_func) = bwdfn1_a0_1;
    return 4;
  } else {
    return bwdfn2( state, next_func );
  }
}

static int bwdfn0_a0_1( const state_t *state, void *next_func )
{
  *((funcptr *)next_func) = bwdfn1;
  return 25;
}

static int bwdfn0( const state_t *state, void *next_func )
{
  if( state->vars[ 0 ] == 0 ) {
    *((funcptr *)next_func) = bwdfn0_a0_1;
    return 1;
  } else {
    return bwdfn1( state, next_func );
  }
}


#define init_history 0

#define max_fwd_children 48

/* NOTE: FOR ALL OF THE MOVE ITERATOR DEFINITIONS funcptr
   MUST BE A VARIABLE. */

/* initialise a forward move iterator */
#define init_fwd_iter( ruleid_iter, state ) { \
  (*ruleid_iter).my_funcptr = fwdfn0 ; \
  (*ruleid_iter).my_state = state; \
}

/* use iterator to generate next applicable rule to apply 
   returns rule to use, -1 if there are no more rules to apply */
#define next_ruleid( ruleid_iter ) (((*ruleid_iter).my_funcptr)?((*ruleid_iter).my_funcptr)((*ruleid_iter).my_state,&((*ruleid_iter).my_funcptr)):-1)

/* apply a rule to a state */
#define apply_fwd_rule( rule, state, result ) fwd_rules[(rule)](state,result)
/* returns 0 if the rule is pruned, non-zero otherwise */
#define fwd_rule_valid_for_history( history, rule_used ) (fwd_prune_table[(history)+(rule_used)])
/* generate the next history from the current history and a rule */
#define next_fwd_history( history, rule_used ) (fwd_prune_table[(history)+(rule_used)])


static const int bw_max_children = 48;
#define max_bwd_children 48

/* initialise a backwards move iterator */
#define init_bwd_iter( ruleid_iter, state ) { \
  (*ruleid_iter).my_funcptr = bwdfn0 ; \
  (*ruleid_iter).my_state = state; \
}

/* apply a rule to a state */
#define apply_bwd_rule( rule, state, result ) bwd_rules[(rule)](state,result)
/* returns 0 if the rule is pruned, non-zero otherwise */
#define bwd_rule_valid_for_history( history, rule_used ) (bwd_prune_table[(history)+(rule_used)])
/* generate the next history from the current history and a rule */
#define next_bwd_history( history, rule_used ) (bwd_prune_table[(history)+(rule_used)])


/* returns 1 if state is a goal state, 0 otherwise */
static int is_goal( const state_t *state )
{
  if( state->vars[ 0 ] == 0 && state->vars[ 1 ] == 1 && state->vars[ 2 ] == 2 && state->vars[ 3 ] == 4 && state->vars[ 4 ] == 3 && state->vars[ 5 ] == 5 && state->vars[ 6 ] == 6 && state->vars[ 7 ] == 7 && state->vars[ 8 ] == 8 && state->vars[ 9 ] == 9 && state->vars[ 10 ] == 10 && state->vars[ 11 ] == 11 && state->vars[ 12 ] == 12 && state->vars[ 13 ] == 13 && state->vars[ 14 ] == 14 && state->vars[ 15 ] == 15 ) {
    return 1;
  }
  return 0;
}

static void init_goal_state( state_t *state, int goal_rule )
{
  switch( goal_rule ) {
  case 0:
    state->vars[ 0 ] = 0;
    state->vars[ 1 ] = 1;
    state->vars[ 2 ] = 2;
    state->vars[ 3 ] = 4;
    state->vars[ 4 ] = 3;
    state->vars[ 5 ] = 5;
    state->vars[ 6 ] = 6;
    state->vars[ 7 ] = 7;
    state->vars[ 8 ] = 8;
    state->vars[ 9 ] = 9;
    state->vars[ 10 ] = 10;
    state->vars[ 11 ] = 11;
    state->vars[ 12 ] = 12;
    state->vars[ 13 ] = 13;
    state->vars[ 14 ] = 14;
    state->vars[ 15 ] = 15;
    break;
  }
}

/* get the first goal state and initialise iterator */
#define first_goal_state( state_ptr, int_ptr_goal_iter ) init_goal_state(state_ptr,*(int_ptr_goal_iter)=0)

/* get the next goal state
   returns 1 if there is another goal state, 0 otherwise */
static int8_t next_goal_state( state_t *state, int *goal_iter )
{
  switch( *goal_iter ) {
  case 0:
    return 0;
  }
  return 0;
}

