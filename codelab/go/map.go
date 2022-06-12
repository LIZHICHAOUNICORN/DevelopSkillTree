package main

import "fmt"

func main(){

    m := make(map[string]interface{})
    m["int"] = 123

    for key,value := range m {
        fmt.Printf("key: %s, value: %d \n", key, value)
    }

}

