"""Import some Python modules that will
prove useful when creating this web application"""

import sqlite3
from flask import Flask, redirect, render_template, request

# Configure application
app = Flask(__name__)

# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True

# Configure the database
database = './birthdays.db'

# Ensure responses aren't cached
@app.after_request
def after_request(response):
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response

# Create a web application that keeps track of friends’ birthdays.
@app.route("/", methods=["GET", "POST"])
def index():

        #  Call sqlite3.connect() to create a connection to the database
        con = sqlite3.connect(database)

        """Create a 'dictionary cursor', that is, return
                'dictionary' rows instead of tuples"""
        con.row_factory = sqlite3.Row

        """Use the following method so you can execute SQL statements
                    and fetch results from SQL queries"""
        cursor = con.cursor()

    # User reached route via POST (as by submitting a form via POST)
        if request.method == "POST":

        # Get at the data provided via the form
            name = request.form.get("name")
            month = request.form.get("month")
            day = request.form.get("day")

            # Having provided all the data add it to the database
            cursor.execute("INSERT INTO birthdays (name, month, day) VALUES (?, ?, ?)", (name, month, day))

            # Call con.commit() on the connection object to commit the transaction:
            con.commit()

            # If all is well and good, redirect the user to a page default state
            return redirect("/")

            # User reached route via GET (as by submitting a form via GET)
        else:

            # Query the database for all the birthday dates
            birthdays = cursor.execute("SELECT *FROM birthdays")

            # Fetch all the remaining tuples from the last executed statement from a table
            birthdays = cursor.fetchall()

            # Display the entries in the database via index.html template
            return render_template("index.html", birthdays=birthdays)