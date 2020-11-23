from flask import *
import pyrebase
import sys
import os
from dotenv import load_dotenv
from datetime import datetime


load_dotenv()

config = {
    "apiKey": os.getenv("APIKEY"),
    "authDomain": os.getenv("AUTHDOMAIN"),
    "databaseURL": os.getenv("DATABASEURL"),
    "projectId": os.getenv("PROJECTID"),
    "storageBucket": os.getenv("STORAGEBUCKET"),
    "messagingSenderId": os.getenv("MESSAGINGSENDERIF"),
}

firebase = pyrebase.initialize_app(config)
db = firebase.database()


app = Flask(__name__)


def hex_to_rgb(value):
    value = value.lstrip("#")
    lv = len(value)
    return tuple(int(value[i : i + lv // 3], 16) for i in range(0, lv, lv // 3))


@app.route("/", methods=["GET", "POST"])
def home():
    lsts = []
    users = db.child("users/user/").get()
    for user in users.each():
        lsts.append(user.val())
    print(lsts)

    if request.method == "POST":
        if request.form["submit"] == "add":
            dataList = [
                request.form.get("fname"),
                request.form.get("timerVals"),
                request.form.get("reminderCup"),
                request.form.get("emptyCup"),
                request.form.get("fullCup"),
                request.form.get("drinktotal"),
            ]
            data = [
                {"name": dataList[0]},
                {"remindertime": int(dataList[1])},
                {"hexempty": dataList[3]},
                {"hexfull": dataList[4]},
                {"hexreminder": dataList[2]},
                {"drinkToday": int(dataList[5])},
            ]
            c = 0
            for n in data:
                db.child("users").child("user").update(data[c])
                c += 1

            db.child("users").child("user").child("drinktotal").child(
                datetime.today().strftime("%Y-%m-%d")
            ).update(data[5])

            lsts = []
            users = db.child("users/user/").get()
            for user in users.each():
                lsts.append(user.val())

            return render_template(
                "home.html",
                timerVals=int(lsts[7]),
                fname=str(lsts[6]),
                reminderCup=lsts[4],
                emptyCup=lsts[2],
                fullCup=lsts[3],
                drinkTotal=(lsts[0]),
            )
    return render_template(
        "home.html",
        timerVals=int(lsts[7]),
        fname=str(lsts[6]),
        reminderCup=lsts[4],
        emptyCup=lsts[2],
        fullCup=lsts[3],
        drinkTotal=(lsts[0]),
    )


@app.route("/testing")
def test():
    todo = db.child("users").get()
    to = todo.each()
    usernames = []
    for user in todo.each():
        usernames.append(user.key())
    print(usernames)
    return render_template("select.html", usernames=usernames)


if __name__ == "__main__":
    app.run(debug=True)