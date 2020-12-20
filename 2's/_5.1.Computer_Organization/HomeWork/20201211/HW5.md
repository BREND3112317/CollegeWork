# Homework 5

### 1. 設使用 32 位元整數、以位元組定址的機器，若欲儲存十六進數值 1234 於位址 0 :
- 表示出該值如何儲存於大的端機器中
    ```
    00 00 12 34
    ```
- 表示出該值如何儲存於小的端機器中
    ```
    32 12 00 00
    ```
- 若欲將十六進值增大至 123456，在哪一種位元組安置方法、即大的或小的端中會較有效率? 並說明之
    ```
    小的端，因為只要在開頭進行增大即可
    ```

### 2. 表示出字組大小是 32 位元、以位元組定址的機器會如何以小的端以及大的端格式儲存下列數值。設各值均儲存於位址開始於 1016 的位置。畫一記憶體圖示，就各值對應兩種格式分別將數值置入標註了位址的正確記憶體位置中。
- 0x456789A1

||大的端|小的端|
|-|-|-|
|0x10|||
|0x11|||
|0x12|||
|0x13|||
- 0x0000058A

||大的端|小的端|
|-|-|-|
|0x10|||
|0x11|||
|0x12|||
|0x13|||
- 0x14148888

||大的端|小的端|
|-|-|-|
|0x10|||
|0x11|||
|0x12|||
|0x13|||

### 3. 設以 16 位元儲存數值且機器採二德補數表示法，試完成下表。

|整數|二進制|十六進制|四位元組大的端(記憶體中以十六進值表示)|四位元組小的(記憶體中以十六進值表示)|
|:-:|:-:|:-:|:-:|:-:|
|28|0000 0000 0000 0000 0000 0000 0001 1100|0000 001C|0000 001C|1C00 0000|
|2216|0000 0000 0000 0000 0000 1000 1010 1000|0000 08A8|0000 08A8|A808 0000|
|-18675|1111 1111 1111 1111 1011 0111 0000 1101|FFFF B70D|FFFF B70D|0DB7 FFFF|
|-12|1111 1111 1111 1111 1111 1111 1111 0100|FFFF FFF4|FFFF FFF4|F4FF FFFF|
|31456|0000 0000 0000 0000 0111 1010 1110 0000|0000 7AE0|0000 7AE0|E07A 0000|

### 11. 將下列表示式由中置轉換為反波蘭(後置)表示式
- (8-6)/2
    ```
    8 6 + 2 /
    ```
- (2+3)×8/10
    ```
    2 3 + 8 × 10 /
    ```
- (5×(4+3)×2-6)
    ```
    5 4 3 + × 2 × 6 -
    ```

### 12. 將下列表示式由中置轉換為反波蘭(後置)表示式
- X × Y + W × Z + V × U
    ```
    X Y × W Z × V U × + +
    ```
- W × X + W × (U × V + Z)
    ```
    W X × W U V × Z + × +
    ```
- (W × (W + Y × (U × V)))/(U × (X + Y))
    ```
    W W Y U V × × + × U X Y + × /
    ```
### 19. 設暫存器共 32 個，則 16 位元的指令是否可能以擴充的運作碼來編碼下列指令群? 若是，表示其編碼。若否，說明之。

### 21. 
記憶體
|||
|-|-|
|0x1000|0x1400|
|0x1100|0x400|
|0x1200|0x100|
|0x1300|0x1100|
|0x1400|0x1300|
### 23. 

### 26. 