#include <iostream>
using namespace std;

struct TrainCar {
    int cargo;
    TrainCar* nextCar;
};

TrainCar* firstCar = nullptr;

TrainCar* createCar(int value) {
    TrainCar* newCar = new TrainCar;
    newCar->cargo = value;
    newCar->nextCar = nullptr;
    return newCar;
}

void addCarToFront(int value) {
    TrainCar* newCar = createCar(value);
    newCar->nextCar = firstCar;
    firstCar = newCar;
    cout << "Added car carrying " << value << " to the front.\n";
}

void addCarToBack(int value) {
    TrainCar* newCar = createCar(value);
    if (!firstCar) {
        firstCar = newCar;
    } else {
        TrainCar* currentCar = firstCar;
        while (currentCar->nextCar) {
            currentCar = currentCar->nextCar;
        }
        currentCar->nextCar = newCar;
    }
    cout << "Added car carrying " << value << " to the back.\n";
}

void addCarAtPosition(int value, int position) {
    if (position <= 0) {
        cout << "Invalid position.\n";
        return;
    }
    if (position == 1) {
        addCarToFront(value);
        return;
    }

    TrainCar* newCar = createCar(value);
    TrainCar* currentCar = firstCar;
    for (int i = 1; i < position - 1 && currentCar; ++i) {
        currentCar = currentCar->nextCar;
    }

    if (!currentCar) {
        cout << "Position out of range.\n";
        delete newCar;
        return;
    }

    newCar->nextCar = currentCar->nextCar;
    currentCar->nextCar = newCar;
    cout << "Added car carrying " << value << " at position " << position << ".\n";
}

void removeCarFromFront() {
    if (!firstCar) {
        cout << "The train is empty.\n";
        return;
    }
    TrainCar* carToRemove = firstCar;
    firstCar = firstCar->nextCar;
    delete carToRemove;
    cout << "Removed car from the front.\n";
}

void removeCarFromBack() {
    if (!firstCar) {
        cout << "The train is empty.\n";
        return;
    }
    if (!firstCar->nextCar) {
        delete firstCar;
        firstCar = nullptr;
        cout << "Removed car from the back.\n";
        return;
    }

    TrainCar* currentCar = firstCar;
    while (currentCar->nextCar && currentCar->nextCar->nextCar) {
        currentCar = currentCar->nextCar;
    }

    delete currentCar->nextCar;
    currentCar->nextCar = nullptr;
    cout << "Removed car from the back.\n";
}

void removeCarAtPosition(int position) {
    if (position <= 0 || !firstCar) {
        cout << "Invalid position or train is empty.\n";
        return;
    }

    if (position == 1) {
        removeCarFromFront();
        return;
    }

    TrainCar* currentCar = firstCar;
    for (int i = 1; i < position - 1 && currentCar; ++i) {
        currentCar = currentCar->nextCar;
    }

    if (!currentCar || !currentCar->nextCar) {
        cout << "Position out of range.\n";
        return;
    }

    TrainCar* carToRemove = currentCar->nextCar;
    currentCar->nextCar = carToRemove->nextCar;
    delete carToRemove;
    cout << "Removed car at position " << position << ".\n";
}

void showTrain() {
    if (!firstCar) {
        cout << "The train is empty.\n";
        return;
    }

    TrainCar* currentCar = firstCar;
    cout << "Train: ";
    while (currentCar) {
        cout << currentCar->cargo << " -> ";
        currentCar = currentCar->nextCar;
    }
    cout << "END OF TRAIN\n";
}

void findCargo(int value) {
    TrainCar* currentCar = firstCar;
    int position = 1;

    while (currentCar) {
        if (currentCar->cargo == value) {
            cout << "Cargo " << value << " found in car at position " << position << ".\n";
            return;
        }
        currentCar = currentCar->nextCar;
        ++position;
    }

    cout << "Cargo " << value << " not found in the train.\n";
}

void cleanUpTrain() {
    while (firstCar) {
        TrainCar* carToRemove = firstCar;
        firstCar = firstCar->nextCar;
        delete carToRemove;
    }
}

int main() {
    int choice, value, position;

    do {
        cout << "\n--- Train Management Menu ---\n";
        cout << "1. Add car to front\n";
        cout << "2. Add car to back\n";
        cout << "3. Add car at position\n";
        cout << "4. Remove car from front\n";
        cout << "5. Remove car from back\n";
        cout << "6. Remove car at position\n";
        cout << "7. Show the train\n";
        cout << "8. Find cargo\n";
        cout << "9. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter cargo to add to the front: ";
                cin >> value;
                addCarToFront(value);
                break;
            case 2:
                cout << "Enter cargo to add to the back: ";
                cin >> value;
                addCarToBack(value);
                break;
            case 3:
                cout << "Enter cargo to add: ";
                cin >> value;
                cout << "Enter position: ";
                cin >> position;
                addCarAtPosition(value, position);
                break;
            case 4:
                removeCarFromFront();
                break;
            case 5:
                removeCarFromBack();
                break;
            case 6:
                cout << "Enter position to remove: ";
                cin >> position;
                removeCarAtPosition(position);
                break;
            case 7:
                showTrain();
                break;
            case 8:
                cout << "Enter cargo to search: ";
                cin >> value;
                findCargo(value);
                break;
            case 9:
                cout << "Exiting program.\n";
                break;
            default:
                cout << "Invalid choice. Try again.\n";
        }
    } while (choice != 9);

    cleanUpTrain();
    return 0;
}