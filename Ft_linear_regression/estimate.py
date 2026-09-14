from pathlib import Path


PROJECT_DIR = Path(__file__).resolve().parent


def read_thetas():
    try:
        thetas = open(PROJECT_DIR / "thetas", "r")
        theta = thetas.read().split(",")
        theta = [float(i) for i in theta]
        thetas.close()
    except BaseException:
        return [0, 0]

    return theta


def estimate_price(theta0, theta1, mileage):
    return theta0 + (theta1 * mileage)


def main():
    try:
        mileage = input("Enter mileage: ")
        mileage = float(mileage)
        thetas = read_thetas()
        price = estimate_price(thetas[0], thetas[1], mileage)
        print("Estimated price: ", price)
    except BaseException:
        print("Error during estimation")
        exit()


if __name__ == "__main__":
    main()