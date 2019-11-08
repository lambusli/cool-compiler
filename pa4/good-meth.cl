class Queen {
    pane : Int;
};

class King inherits Queen {};

class Bishop inherits Queen {
    soldier : Int;
};

class A inherits King {
    xA1 : Undef;
    xA2 : Undef <- 5; 
};
