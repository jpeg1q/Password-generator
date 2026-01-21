import random
p = True
while p:
    long = input("How long should the password be?: ")
    fav = input("what is your favorite number?: ")
    name = input("Give a food name: ")
    shoe = input("What brand of shoes you wear?: ")
    short = input("What color is your shirt: ")

    io = list(str(hash(fav)))
    io1 = list(name)
    io2 = list("~!@#$%^&*()_+`-={}|[]:"'<>?,./')
    io3 = list(shoe)
    io4 = list(short)
    io45 = list(str(hash(short)))
    ol = [io,io1,io2,io3]
    password = ""
    for i in range(int(long)):
        po = random.choice(ol)
        password += random.choice(po)

    print("Your new password is: ", password)
    shuffle = input("Do you want to shuffle your password? y/n: ")
    if shuffle == "y":
        l = list(password)
        random.shuffle(l)
        print(l)
        p = False
    elif shuffle == "n":
                p = False
