from bs4 import BeautifulSoup
from selenium import webdriver
from selenium.webdriver.common.keys import Keys
import time
#target web link
url = "https://store.nike.com/us/en_us/pw/mens-clearance/47Z7pu"
#use safari open the web
browser = webdriver.Safari()
browser.get(url)

##scroll down the page(from https://michaeljsanders.com/2017/05/12/scrapin-and-scrollin.html)
#lenOfPage = browser.execute_script("window.scrollTo(0, document.body.scrollHeight);var lenOfPage=document.body.scrollHeight;return lenOfPage;")
#match=False
#while(match==False):
#    lastCount = lenOfPage
#    time.sleep(3)
#    lenOfPage = browser.execute_script("window.scrollTo(0, document.body.scrollHeight);var lenOfPage=document.body.scrollHeight;return lenOfPage;")
#    if lastCount==lenOfPage:
#        match=True

##scroll down the page
elem = browser.find_element_by_tag_name("html")
for i in range(1,20):
    elem.send_keys(Keys.END)
    time.sleep(3)

#grab the html page
html = browser.page_source
#html pare
soup = BeautifulSoup(html,'lxml')
#grab each item
items = soup.findAll("div",{"class":"grid-item fullSize"})
browser.close()
filename = "products.csv"
f = open(filename,"w")

headers = "Name, Discount Price, Original Price, Discount Rate, Link\n"
f.write(headers)

for item in items:
    #grab item name
    name = item.p.text
    #grab each product
    products = item.findAll("a",{"class":"color-chip"})
    for product in products:
        #grab discount price
        disP = product["data-lp"].replace("$","")
        #grab original price
        oriP = product["data-op"].replace("$","")
        #calculate discount rate
        disR = (1 - float(disP) / float(oriP)) * 100
        #grab web link
        link = product["href"]

        #print to console
        print("Name: " + name)
        print("Discount Price: " + disP)
        print("Original Price: " + oriP)
        print("Discount Rate: " + str(disR))
        print("Link: " + link)

        #write to file
        f.write(name + ", " + disP + ", " + oriP + ", " + str(disR) + ", " + link + "\n")

f.close()

