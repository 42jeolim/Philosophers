# Philosophers

## Philosopher 과제
n명의 철학자가 원탁에 앉아 있고, 식탁 가운데에는 스파게티가 있고 양옆에 포크가 하나씩 있다.
각각의 철학자는 다른 철학자에게 말을 할 수 없다.
철학자가 스파게티를 먹기 위해서는 양 옆의 포크를 동시에 들어야 한다.

## 과제 설명
1. [number_of_philosophers] [time_to_die] [time_to_eat] [time_to_sleep] [number_of_times_each_philosopher_must_eat]을 입력 값으로 ㅂ다는다
2. 양쪽 포크를 잡으면 일정 시간만큼 식사를 한다
3. 포크를 내려놓는다
4. 일정 시간 잠을 잔다
5. 생각을 하다 배가 고프면 2번으로 돌아간다


---------------------------------------

## How to run Philosopher
* compile mendatory part
```bash
make all
```

* run philosopher
```bash
./philo [number_of_philosophers] [time_to_die] [time_to_eat] [time_to_sleep] [number_of_times_each_philosopher_must_eat]
```
  * example
  ```bash
  ./philo 4 410 200 200
  ```
---------------------------------------

## Test
* should die : 1 800 200 200
* no one die : 4 310 200 200
* no one die : 5 800 200 200
* should die : 5 800 200 200 7
* should die : 2 310 200 100
200이상의 철학자 수나 60이하의 시간입력은 금지!
