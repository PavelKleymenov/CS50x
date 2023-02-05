"""Implement a website via which users can “buy” and “sell” stocks"""
import os

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.security import check_password_hash, generate_password_hash
from werkzeug.exceptions import default_exceptions, HTTPException, InternalServerError
from helpers import apology, login_required, lookup, usd
from datetime import datetime

# Configure the application
app = Flask(__name__)

# Make sure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True

# Customize the currency filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure the database
db = SQL("sqlite:///finance.db")

# Render an apology if the API key has not been set
if not os.environ.get("API_KEY"):
    raise RuntimeError("API_KEY not set")

# Ensure responses aren't cached
@app.after_request
def after_request(response):
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response

"""Implement a function that showcases users investment portfolio"""
@app.route("/")
@login_required
def index():

    # Query for a stock package related information of the user currently logged in
    rows = db.execute("SELECT symbol, SUM(shares) FROM activities WHERE user_id = ? \
    GROUP BY symbol HAVING SUM(shares) > 0", session["user_id"])

    """Create an empty list that will be populated with a stock symbol,
    as well as the number of shares and the current price thereof, once the
                    user gets something into his package"""
    package = []

    """Create a counter variable that tracks the total value of user' holdings,
            namely, the value of stocks he owns plus the cash he possesses"""
    assets = 0

    for row in rows:

        # Identify stock symbol
        stock = lookup(row['symbol'])

        """Calculate the total value of all the shares of
            a particular symbol that the user owns"""
        sum_value = (stock["price"] * row["SUM(shares)"])

        # Populate the index table with all the relevant content
        package.append({"symbol": stock["symbol"], "name": stock["name"],
                        "shares": row["SUM(shares)"], "price": usd(stock["price"]), "total": usd(sum_value)})

        # Update the total based upon what user' package comprised of
        assets += stock["price"] * row["SUM(shares)"]

    # Calculate how much cash the user currently has
    rows = db.execute("SELECT cash FROM users WHERE id = ?", session["user_id"])
    cash = rows[0]["cash"]

    # Modify the total cash value the user currently logged in has
    assets += cash

    # Render a template displaying the package of the person currently logged in
    return render_template("index.html", package=package, cash=usd(cash), assets=usd(assets))

"""Implement a function that allows users to buy a particular stock"""
@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():

    # User reached route via POST method
    if request.method == "POST":

        # Require provision of the stock symbol
        symbol = request.form.get("symbol")

        # Require provision of the symbol as per the return value of the 'lookup' helper function
        stock = lookup(symbol.upper())

        # Require users to provide a number of shares they would like to purchase
        try:
            shares = int(request.form.get("shares"))
        except:
            return apology("Can't cast a string")

        # Render an apology if the user hasn't specified which stock he's interested in buying
        if not symbol:
            return apology("Must provide symbol")

        # Render an apology if the user has provided a stock which is not valid
        if not stock:
            return apology("Must provide valid symbol")

        # Render an apology if the user has not specified the number of stocks for purchase
        if not shares:
            return apology("Must purchase at least one stock")

        # Render an apology if the user provided invalid number of shares
        if shares < 0:
            return apology("Must provide a valid number of shares")

        # Store the information about the user in a variable called user_id
        user_id = session["user_id"]

        # Utilize a 'lookup' helper to get at stock' current price
        price = (stock)["price"]

        # Query the database to find out how much cash the user currently has
        balance = db.execute("SELECT cash FROM users WHERE id = ?", user_id)

        # Get at user' cash by indexing into a database
        user_cash = balance[0]["cash"]

        # Store the total value of a transaction in a corresponding variable
        transaction_value = float(price) * shares

        # Render an apology if the user doesn't have enough cash to complete a purchase
        if user_cash < transaction_value:
            return apology("Insufficient funds, transaction can not be completed")

        # Identify current date and time
        now = datetime.now()

        # Convert date, time and datetime objects to its equivalent string
        date = now.strftime("%d/%m/%Y %H:%M:%S")

        # Determine what the value of user' cash will be once a transaction completed
        now_cash = user_cash - transaction_value

        # Update user' cash balance once the purchase has been made
        db.execute("UPDATE users SET cash = ? WHERE id = ?", now_cash, user_id)

        # Set down a transaction
        db.execute("INSERT INTO activities (user_id, symbol, shares, price, date) \
        VALUES (?, ?, ?, ?, ?)", user_id, stock["symbol"], shares, price, date)

        # Make sure to notify the user of successfully completed transaction
        flash("Stock has been successfully purchased")

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET method
    else:
        return render_template("buy.html")

"""Implement a function that shows a history of all the
            transactions a given user has made"""
@app.route("/history")
@login_required
def history():

    user_id = session["user_id"]

    # Query for the data that you want to display
    transactions = db.execute("SELECT symbol, shares, price, date FROM activities \
    WHERE user_id = ?", user_id)

    """Iterate over all transactions a given user has ever made, so as to display their complete history"""
    for i in range(len(transactions)):
        transactions[i]["price"] = usd(transactions[i]["price"])
    return render_template("history.html", transactions=transactions)

"""Implement a function that logs users in"""
@app.route("/login", methods=["GET", "POST"])
def login():

    # Remove all keys and values from the session-state collection
    session.clear()

    # User reached route via POST method
    if request.method == "POST":

        # Make sure the username was submitted
        if not request.form.get("username"):
            return apology("must provide username")

        # Make sure the password was submitted
        elif not request.form.get("password"):
            return apology("must provide password")

        # Query database for the username
        rows = db.execute("SELECT * FROM users WHERE username = ?", request.form.get("username"))

        # Make sure provided data is correct
        if len(rows) != 1 or not check_password_hash(rows[0]["hash"], request.form.get("password")):
            return apology("invalid username and/or password")

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET method
    else:
        return render_template("login.html")

"""Implement a function that logs users out"""
@app.route("/logout")
def logout():

    # Remove all keys and values from the session-state collection
    session.clear()

    # Redirect user to login form
    return redirect("/")

"""Implement a function that allows users to search
        for further info about a given stock"""
@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():

    # User reached route via POST
    if request.method == "POST":

        # Get at the data received in a Flask request
        symbol = request.form.get("symbol")

        # Query for a particular stock symbol
        result = lookup(symbol)

        # Render an apology if user searched for an invalid stock
        if not result:
            return apology("No such stock exists")

        """If, though, the stock has been found, render a template,
          presenting all the information pertinent to that stock"""
        return render_template("quoted.html", name=result["name"], price=usd(result["price"]), symbol=result["symbol"])

    # User reached route via GET
    else:
        return render_template("quote.html")

# Implement a function that allows users to sign up for an account
@app.route("/register", methods=["GET", "POST"])
def register():

    # User reached route via GET
    if request.method == "GET":
        return render_template("register.html")

    # User reached route via POST method
    else:

        # Get at the data received in a Flask request
        username = request.form.get("username")
        password = request.form.get("password")
        confirmation = request.form.get("confirmation")

        # Render an apology if the user has omitted typing in a username
        if not username:
            return apology("Must provide username")

        # Render an apology if the user has omitted typing in a password
        if not password:
            return apology("Must provide password")

        # Render an apology if the user has omitted password verification
        if not confirmation:
            return apology("Password must be confirmed")

        # Render an apology if the user has failed to confirm their password
        if password != confirmation:
            return apology("Passwords don't match, try again, please")

        # Encrypt the password for security purposes
        hash = generate_password_hash(password)

        # Having gone through all preliminary steps, try adding the user to the database
        try:
            db.execute("INSERT INTO users (username, hash) VALUES(?, ?)",
                              request.form.get("username"), hash)
        except:

            # Render an apology if the username provided by the user already exists
            return apology("Username already exists")

        # Redirect user to home page
        return redirect("/")

"""Implement a function that allows users to trade the stocks they own"""
@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():

    # if user reached route via POST method
    if request.method == "POST":

        # Get at the data received in a Flask request
        symbol = request.form.get("symbol")
        shares = int(request.form.get("shares"))
        stock = lookup(symbol.upper())

        # Render an apology if the user has failed to select a stock symbol
        if not symbol:
            return apology("Must select a stock symbol")

        # Render an apology if the user has failed to specify how many shares of a stock is up for sale
        if not shares:
            return apology("Must provide a number of shares")

        # Render an apology if the user has provided an invalid number of shares
        if shares < 0:
            return apology("Must provide a valid number of shares")

        # Check whether the user currently logged in actually owns the required number of stocks
        rows = db.execute("SELECT symbol, SUM(shares) FROM activities WHERE user_id = ? \
        GROUP BY symbol HAVING SUM(shares) > 0", session["user_id"])

        # Render an apology if the user has tried to sell more stocks than he actually owns
        for row in rows:
            if row["symbol"] == symbol:
                if shares > row["SUM(shares)"]:
                    return apology("Must provide the number of stocks you can actually sell")

        # Caclulate the cost of a transaction and store it into a corresponding variable
        transaction = shares * stock['price']

        # Identify current date and time
        now = datetime.now()

        # Convert date, time and datetime objects to its equivalent string
        date = now.strftime("%d/%m/%Y %H:%M:%S")

        # Calculate the user' cash once transaction has been made
        db.execute("UPDATE users SET cash = cash + :transaction \
        WHERE id =:id", transaction=transaction, id=session["user_id"])

        # Add transaction to a database
        db.execute("INSERT INTO activities (user_id, symbol, shares, price, date) \
        VALUES (?, ?, ?, ?, ?)", session["user_id"], stock["symbol"],
                   -int(request.form.get("shares")), stock["price"], date)

        # Redirect user to a homepage
        return redirect("/")

        # User reached route via GET method
    else:
        rows = db.execute("SELECT symbol FROM activities WHERE user_id = ? \
        GROUP BY symbol HAVING SUM(shares) > 0", session["user_id"])
        return render_template("sell.html", symbols=[row["symbol"] for row in rows])

"""Implement a function that allows user to cancel their account"""
@app.route("/deregister", methods=["GET", "POST"])
def deregister():

    # User reached route via GET method
    if request.method == "GET":
        return render_template("deregister.html")

    # User reached route via POST method
    else:
        # Get at the data received in a Flask request
        username = request.form.get("username")
        password = request.form.get("password")

        # Render an apology if the user has failed to specify which account needs to be cancelled
        if not username:
            return apology("The username has to be provided")

        # Render an apology if the user has omitted verifying his identity by typing in a password
        if not password:
            return apology("The password has to be provided")

        # Query database for username
        rows = db.execute("SELECT * FROM users WHERE username = ?", request.form.get("username"))

        # Make sure the user has provided valid username and password
        if len(rows) != 1 or not check_password_hash(rows[0]["hash"], request.form.get("password")):
            return apology("invalid username and/or password")

        # Once the user has validated their identity, remove all of the data from the database
        rows = db.execute("DELETE FROM users WHERE username = ?", username)

        # Redirect user to a homepage
        return redirect("/")

# Implement a function that handles errors
def errorhandler(e):
    if not isinstance(e, HTTPException):
        e = InternalServerError()
    return apology(e.name, e.code)


# Listen for errors
for code in default_exceptions:
    app.errorhandler(code)(errorhandler)