class Queen {};

class King inherits Queen {};

class A {
    tempK : King;
    tempQ : Queen;
    x : Int <- (tempK <- tempQ); -- You cannot assign sth superior to sth inferior
};
