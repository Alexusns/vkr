CREATE TABLE account(
    account_id SERIAL PRIMARY KEY,
    email VARCHAR(256) NOT NULL,
    pass_hash VARCHAR(256) NOT NULL
);
CREATE TABLE product(
    product_id SERIAL PRIMARY KEY,
    name VARCHAR(256) NOT NULL ,
    cost DECIMAL(10, 2) NOT NULL,
    description VARCHAR(256) NOT NULL
);
CREATE TABLE product_account(
    product INT NOT NULL,
    account INT NOT NULL,
    amount INT NOT NULL,
    PRIMARY KEY (product, account),
    FOREIGN KEY (product) REFERENCES product(product_id),
    FOREIGN KEY (account) REFERENCES account(account_id)
);