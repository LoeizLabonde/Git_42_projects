# Linear Regression Flow

```mermaid
flowchart TD
    A["data.csv\nMileage, price"] --> B["train.py\nlin_reg()"]

    B --> C["read_data()\nutils.py"]
    C --> D["Separate raw mileage\nand raw price"]
    D --> E["Standardize mileage\n(x - mean) / std_dev"]

    E --> F["Initialize theta0, theta1\nand learning rate"]
    F --> G{"Training loop\nup to 1000 epochs"}
    G --> H["estimate_price(theta0, theta1, x)"]
    H --> I["Compute errors and\nmean absolute loss"]
    I --> J["Update theta0 and theta1\nwith gradient descent"]
    J --> K{"Loss unchanged\nwhen rounded to 7 decimals?"}
    K -->|"No"| G
    K -->|"Yes"| L["Convert parameters back\nto the original mileage scale"]
    G -->|"Maximum epochs reached"| L

    L --> M["plot_final_state()\ntraining.png"]
    L --> N["plot_loss()\nloss.png"]
    L --> O["store_thetas()\nthetas"]

    O --> P["estimate.py\nread_thetas()"]
    Q["User enters mileage"] --> P
    P --> R["estimate_price(theta0, theta1, mileage)"]
    R --> S["Estimated price"]

    classDef input fill:#e8f1ff,stroke:#2563eb,color:#172554
    classDef process fill:#eefbf3,stroke:#16a34a,color:#14532d
    classDef decision fill:#fff7ed,stroke:#ea580c,color:#7c2d12
    classDef output fill:#fdf2f8,stroke:#db2777,color:#831843

    class A,Q input
    class B,C,D,E,F,H,I,J,L,P,R process
    class G,K decision
    class M,N,O,S output
```

## Files involved

- `data.csv`: training data.
- `train.py`: model initialization, training, plotting, and theta persistence.
- `utils.py`: data loading and plot generation.
- `thetas`: persisted model parameters.
- `estimate.py`: price estimation from a user-provided mileage.
