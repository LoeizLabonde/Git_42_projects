from pathlib import Path

from estimate import estimate_price
from utils import read_data, plot_final_state, plot_loss


PROJECT_DIR = Path(__file__).resolve().parent


class lin_reg:
    def __init__(self, file=PROJECT_DIR / "data.csv"):
        # Init hyperparameters
        self.learning_rate = 0.01
        self.theta0 = 0
        self.theta1 = 0

        # Init data
        self.raw_data = read_data(file)
        self.raw_mileages = [row[0] for row in self.raw_data]
        self.raw_prices = [row[1] for row in self.raw_data]

        # Init metas
        self.mean_mileage = sum(self.raw_mileages) / len(self.raw_mileages)
        self.std_dev_mileage = (
            sum([(mileage - self.mean_mileage) ** 2
                 for mileage in self.raw_mileages]) / len(self.raw_mileages)
        ) ** 0.5
        self.m = len(self.raw_data)

        # Scale data
        self.mileages = [
            (raw_mileage - self.mean_mileage) / self.std_dev_mileage
            for raw_mileage in self.raw_mileages
        ]
        self.prices = self.raw_prices

        # Accumulators
        self.loss_acc = []

    def print_state(self, epoch):
        print(
            "Epoch\t{}\nθ0\t{}\nθ1\t{}\nLoss\t{}\n".format(
                epoch,
                (self.theta0 - self.theta1 * self.mean_mileage
                    / self.std_dev_mileage),
                (self.theta1 / self.std_dev_mileage),
                self.loss_acc[-1],
            )
        )

    def calculate_errors(self):

        t0_error = 0
        t1_error = 0
        total_loss = 0

        for i in range(self.m ):
            prediction = estimate_price(
                self.theta0,
                self.theta1,
                self.mileages[i]
            )
            error = prediction - self.prices[i]
            t0_error += error
            t1_error += error * self.mileages[i]
            total_loss += abs(error)

        total_loss /= self.m
        return t0_error, t1_error, total_loss

    def train(self):

        max_epoch = 1000


        for epoch in range(max_epoch + 1):
            t0_error, t1_error, loss = self.calculate_errors()
            self.theta0 -= self.learning_rate * t0_error
            self.theta1 -= self.learning_rate * t1_error
            self.loss_acc.append(loss)

            if len(self.loss_acc) > 1 and round(self.loss_acc[-1], 7) == round(
                self.loss_acc[-2], 7
            ):
                break

            if (epoch % (max_epoch / 1000)) == 0:
                self.print_state(epoch)

        self.theta0 -= self.theta1 * self.mean_mileage / self.std_dev_mileage
        self.theta1 /= self.std_dev_mileage

        plot_final_state(self)
        plot_loss(self)

    def store_thetas(self):

        try:
            output = open(PROJECT_DIR / "thetas", "w")
            output.write(str(self.theta0) + "," + str(self.theta1))
            output.close()
            
        except BaseException as e:
            print("Error during theta storing: ", e)
            exit()


def main():
    lr = lin_reg()
    lr.train()
    lr.store_thetas()


if __name__ == "__main__":
    main()