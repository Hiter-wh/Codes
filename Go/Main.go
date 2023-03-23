package main

import (
	"container/heap"
	"fmt"
)

var (
	Infinity = 100000000
)

func abs(a int64, b int64) int64 {
	var abS int64

	if a >= b {
		abS = a - b
	} else {
		abS = (b - a)
	}
	return abS
}
func min(a int64, b int64) int64 {
	var r int64
	if a > b {
		r = b

	} else {
		r = a
	}
	return r
}

type Ad_link struct {
	len  int
	v_no int
}

type Ad_table struct {
	aed []Ad_link
}
type E struct {
	p int
	q int
	l int
}

type Heap []E

func (rech Heap) Len() int {
	return len(rech)
}

// 实现sort.Iterface
func (rech Heap) Swap(i, j int) {
	rech[i], rech[j] = rech[j], rech[i]
}

// The lowest heap
func (rech Heap) Less(i, j int) bool {
	return rech[i].l < rech[j].l
}

// 实现heap.Interface接口定义的额外方法
func (rech *Heap) Push(h interface{}) {
	*rech = append(*rech, h.(E))
}
func (rech *Heap) Pop() (x interface{}) {
	n := len(*rech)
	x = (*rech)[n-1]      // 返回删除的元素
	*rech = (*rech)[:n-1] // [n:m]不包括下标为m的元素
	return x
}

func main() {
	edge := 0

	vertices := 0
	s := 0
	t := 0
	fmt.Scanln(&vertices, &edge)
	fmt.Scanln(&s, &t)
	//use adjacent table
	tb := make([]Ad_table, vertices)
	for i := 0; i < vertices; i++ {
		tb[i].aed = make([]Ad_link, 0)
	}
	x := 0
	y := 0
	z := 0
	for i := 0; i < edge; i++ {
		fmt.Scanln(&x, &y, &z)
		//add node to adjacent table
		tb[x].aed = append(tb[x].aed, Ad_link{z, y})
		tb[y].aed = append(tb[y].aed, Ad_link{z, x})
	}
	hp := &Heap{}
	heap.Init(hp)

	used := make([]int, vertices)
	//begin from vertex s
	used[s] = 1
	//Being to Dijkastra
	cur := s
	ans := make([]int, vertices)
	ans[s] = 0
	for ans[t] == 0 {
		if len(tb[cur].aed) != 0 {
			for _, adlink := range tb[cur].aed {

				if used[adlink.v_no] == 0 {
					//put edges into heap
					heap.Push(hp, E{cur, adlink.v_no, adlink.len + ans[cur]})
				}

			}

			var me E
			me = heap.Pop(hp).(E)

			//ensure the edge is unused
			for used[me.p] != 0 && used[me.q] != 0 {
				me = heap.Pop(hp).(E)
			}
			used[me.q] = 1
			cur = me.q
			ans[me.q] = me.l
		}

	}
	fmt.Println(ans[t])
}
