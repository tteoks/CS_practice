# 트리 자료구조 (Tree)

## 개요

트리 (tree) 자료구조는 연관된 두 개의 node가 edge를 통해 연결되어 있는 데이터 집합을 가진 비선형 자료구조이다.

### 특징

* 계층적 구조를 가지고 있는 자료구조
* 탐색과 검색을 효율적으로 할 수 있는 대표적인 자료구조


## 트리 구성

* 노드 (node): 트리를 구성하는 기본 요소
* 간선 (edge): 노드와 노드를 관계를 표현한 선
* 부모 노드 (parent node): 자식 노드 (child node)를 가진 노드
* 자식 노드 (child node): 부모 노드 (parent node)의 하위에 위치한 노드
* 루트 노드 (root node): 트리에서 가장 최상단에 위치한 노드로 부모 노드가 없는 노드
* 리프 노드 (leaf node or external node): 자식 노드를 가지지 않는 최하단에 위치한 노드
* 조상 (ancestor): 해당 노드로부터 루트 노드까지 존재하는 모든 부모 노드
* 자손 (descendant): 해단 서브트리에 존재하는 모든 노드 집합
* 형제 (sibling): 같은 부모 노드를 가진 자식 노드들
* 레벨 (level): 루트 노드로부터 최하단 노드 까지의 깊이 (루트 노드 레벨 = 0)
* 내부 노드 (internal node): 자식 노드를 1개 이상 가지고 있는 노드
* 서브 트리 (sub tree): 트리 구조에서 자손을 가진 노드들

## 트리 종류

|트리 종류|설명|
|---|---|
|Binary tree|자식 노드를 최대 2개까지 가질 수 있는 트리|
|Ternary tree|자식 노드를 최대 3개까지 가질 수 있는 트리|
|Binary search tree|왼쪽 자식 노드들이 부모 노드보다 작고, 오른쪽 자식 노드들이 부모 노드보다 큰 규칙을 가진 이진 트리|
|Complete binary tree|모든 서브트리의 레벨이 같으면서 마지막 레벨의 노드들이 왼쪽부터 채워져있는 이진 트리|
|Full binary tree|자식 노드가 하나도 없거나, 두개 모두 채워져있는 부모노드들로 구성된 이진 트리|
|Perfect binary tree|마지막 레벨을 제외한 모든 노드가 2개의 자식 노드를 가지고 있는 이진 트리|
|Degenerate binary tree|모든 내부노드가 하나의 자식만 가지는 이진 트리|
|Balanced binary tree|모든 노드의 왼쪽, 오른쪽 서브 트리의 레벨 (높이) 차이가 일정한 범위내로 유지되는 이진 트리|

## 트리 사용 사례

* File System: 파일 시스템에서 효율적으로 파일을 조직화하고, 탐색할 수 있게 함
* Data Compression: binary tree를 활용해 데이터 압축 기술로 유묭한 Huffman code에서 이진 트리를 활용해 구현
* Compiler: 컴파일러는 작성된 소스코드를 syntax tree 구조를 활용하여 정보를 추출함
* Database indexing: B-tree를 사용해 효율적으로 데이터를 검색할 수 있도록 함

