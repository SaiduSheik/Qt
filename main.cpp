#include <iostream>
using namespace std;

// Builder design pattern
class Car
{
public:
    explicit Car(string carType):_car{carType} {}
    ~Car(){}

    void setEngine(string type) { _engine = type; }
    void setBody(string body)   { _body = body;   }
    string getEngine()          { return _engine; }
    string getBody()            { return _body;   }

    void show() {
        cout << "Car Type: " <<_car << endl
             << "Body Type: " <<_body << endl
             << "Engine Type: "<<_engine << endl << endl;
    }
private:
    string _car;
    string _body;
    string _engine;

};

// CarBuilder Abstract Class
// Means all builders should have atleast these methods
class CarBuilder
{
public:
    virtual void getPartsDone() = 0;
    virtual void buildBody() = 0;
    virtual void buildEngine() = 0;
    virtual ~CarBuilder(){}
    Car* getCar(){ return _car; }

protected:
    Car *_car;
};


class MaruthiBuilder: public CarBuilder {
public:
    ~MaruthiBuilder(){}
    void getPartsDone() { _car = new Car("Maruthi Car"); }
    void buildEngine()  { _car->setEngine("Maruthi Engine");   }
    void buildBody()    { _car->setBody("Maruthi Body");   }

};

class SuzukiBuilder: public CarBuilder {
public:
    ~SuzukiBuilder(){}
    void getPartsDone() { _car = new Car("Suzuki Car"); }
    void buildEngine()  { _car->setEngine("Suzuki Engine");   }
    void buildBody()    { _car->setBody("Suzuki Body");   }

};

// Defines steps and tells to the builder that build in given order.
class Director{
    //CarBuilder *builder;
public:
    Car* createCar(CarBuilder *builder) {
        builder->getPartsDone();
        builder->buildBody();
        builder->buildEngine();
        return builder->getCar();
    }
};

int main() {

    Director dir;
    MaruthiBuilder mb;
    SuzukiBuilder sb;

    Car *maruthi = dir.createCar(&mb);
    Car *suzuki = dir.createCar(&sb);

    maruthi->show();
    suzuki->show();

    delete maruthi;
    delete suzuki;

    return 0;
}
