/**
 *  Structures to model input
 */

#ifndef EE6A4000_F333_4E98_9AFC_CB23FB2EC80E
#define EE6A4000_F333_4E98_9AFC_CB23FB2EC80E

struct Array {
    int *elements;
    int size;
};

struct Array_2d {
    struct Array *cell;
    int size;
};


#endif /* EE6A4000_F333_4E98_9AFC_CB23FB2EC80E */
