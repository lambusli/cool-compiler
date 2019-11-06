class Queen {};

class King inherits Queen {};

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
    xp : Int <- (temp <- 5);
    tempK : King;
    tempQ : Queen;
    x : Int <- (tempQ <- tempK); -- You cannot assign sth superior to sth inferior
};
