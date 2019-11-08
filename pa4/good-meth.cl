class Queen {
    pane : Int;
};

class King inherits Queen {};

class Bishop inherits Queen {
    soldier : Int;
};

class A inherits King {
    fA1(argc : SELF_TYPE) : King {argc};
    fA2(argc : Int) : SELF_TYPE {new SELF_TYPE};
};

class B inherits A {
};
