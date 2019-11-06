class A {
    x : Bool <- true;
};

class B {
    y : Int <- 10;
};

class C {
    z : String <- "here";
};

class D {
    temp : Int;
    x : Int <- (temp <- 5);
};
