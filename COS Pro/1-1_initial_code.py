'''
# 문제1
배달음식 전문점 운영을 위해 다음과 같이 DeliveryStore 인터페이스와  PizzaStore, Food 클래스를 작성했습니다.

![image](https://s3.ap-northeast-2.amazonaws.com/grepp-cloudfront/programmers_imgs/challengeable-imgs/20180316_deli_python1.png)

* DeliveryStore :
  * DeliveryStore는 배달 음식점의 인터페이스입니다.
  * 배달 음식점은 set_order_list와 get_total_price 함수를 구현해야 합니다.
  * set_order_list 함수는 주문 메뉴의 리스트를 매개변수로 받아 저장합니다.
  * get_total_price 함수는 주문받은 음식 가격의 총합을 return 합니다.

* Food : 
  * Food는 음식을 나타내는 클래스입니다.
  * 음식은 이름(name)과 가격(price)으로 구성되어있습니다.

* PizzaStore
  * PizzaStore는 피자 배달 전문점을 나타내는 클래스이며 DeliveryStore 인터페이스를 구현합니다.
  * menu_list는 피자 배달 전문점에서 주문 할 수 있는 음식의 리스트를 저장합니다.
  * order_list는 주문 받은 음식들의 이름을 저장합니다.
  * set_order_list 함수는 주문 메뉴를 받아 order_list에 저장합니다.
  * get_total_price 함수는 order_list에 들어있는 음식 가격의 총합을 return 합니다.

주문 메뉴가 들어있는 리스트 order_list가 매개변수로 주어질 때, 주문한 메뉴의 전체 가격을 return 하도록 solution 함수를 작성하려고 합니다. 위의 클래스 구조를 참고하여 주어진 코드의 빈칸을 적절히 채워 전체 코드를 완성해주세요.

---
##### 매개변수 설명
주문 메뉴가 들어있는 리스트 order_list가 solution 함수의 매개변수로 주어집니다.

* order_list의 길이는 1 이상 5이하입니댜.
* order_list에는 주문하려는 메뉴의 이름들이 문자열 형태로 들어있습니다.
  * order_list에는 같은 메뉴의 이름이 중복해서 들어있지 않습니다.
* 메뉴의 이름과 가격은 PizzaStore의 생성자에서 초기화해줍니다.

---
##### return 값 설명
주문한 메뉴의 전체 가격을 return 해주세요.

---
##### 예시

| order_list                           | return |
|-------------------------------------|--------|
| ["Cheese", "Pineapple", "Meatball"] | 51600  |
'''

from abc import *
 
class DeliveryStore(metaclass=ABCMeta):
    @abstractmethod
    def set_order_list(self, order_list):
        pass
    
    @abstractmethod
    def get_total_price(self):
        pass
    
class Food:
    def __init__(self, name, price):
        self.name = name
        self.price = price
        
class PizzaStore(DeliveryStore):
    def __init__(self):
        menu_names = ["Cheese", "Potato", "Shrimp", "Pineapple", "Meatball"]
        menu_prices = [11100, 12600, 13300, 21000, 19500];
        self.menu_list = []
        for i in range(5):
            self.menu_list.append(Food(menu_names[i], menu_prices[i]))
        
        self.order_list = []
    
    def set_order_list(self, order_list):
        for order in order_list:
            self.order_list.append(order)

    def get_total_price(self):
        total_price = 0
        for order in self.order_list:
            for menu in self.menu_list:
                if order == menu.name:
                    total_price += menu.price
        return total_price 
            
def solution(order_list):
    delivery_store = PizzaStore()
    
    delivery_store.set_order_list(order_list)
    total_price = delivery_store.get_total_price()
    return total_price

#The following is code to output testcase.
order_list = ["Cheese", "Pineapple", "Meatball"]
ret = solution(order_list)

#Press Run button to receive output. 
print("Solution: return value of the function is", ret, ".")