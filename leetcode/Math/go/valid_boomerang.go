func isBoomerang(points [][]int) bool {
    var v1 = [2]int{points[1][0] - points[0][0], points[1][1] - points[0][1]}
    var v2 = [2]int{points[2][0] - points[0][0], points[2][1] - points[0][1]}

    return v1[0]*v2[1] - v1[1]*v2[0] != 0

}

func main() {}
