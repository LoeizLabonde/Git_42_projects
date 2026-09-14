from pathlib import Path

from estimate import estimate_price
import matplotlib.pyplot as plt


PROJECT_DIR = Path(__file__).resolve().parent


def read_data(file):
    try:
        data = open(file, "r")
        data = data.read().split("\n")
        del data[0]
        del data[-1]
        data = [line.split(",") for line in data]
        data = [[float(element) for element in line] for line in data]
    except BaseException:
        print("Error during data reading")
        exit()

    return data


def plot_final_state(lr):
    plt.figure()
    plt.title("Data and hypothesis")
    plt.xlabel("Mileage")
    plt.ylabel("Price")
    plt.scatter(lr.raw_mileages, lr.raw_prices, color="blue")
    plt.plot(
        [min(lr.raw_mileages), max(lr.raw_mileages)],
        [
            estimate_price(lr.theta0, lr.theta1, min(lr.raw_mileages)),
            estimate_price(lr.theta0, lr.theta1, max(lr.raw_mileages)),
        ],
        "r",
    )
    plt.savefig(PROJECT_DIR / "training.png")
    plt.close()


def plot_loss(lr):
    plt.figure()
    plt.title("Loss over time")
    plt.xlabel("Epoch")
    plt.ylabel("Loss")
    plt.plot([i for i in range(len(lr.loss_acc))], lr.loss_acc, "r")
    plt.savefig(PROJECT_DIR / "loss.png")
    plt.close()