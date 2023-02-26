#include "philo.h"

void freeall(t_data *data)
{
    int i;

    i = -1;
    while (++i < data->n_philo)
    {
        pthread_mutex_destroy(&data->philo[i].left_fork);
        pthread_mutex_destroy(data->philo[i].right_fork);
    }
    free(data->philo);
    pthread_mutex_destroy(&data->message);
    pthread_mutex_destroy(&data->m_stop);
    pthread_mutex_destroy(&data->m_eat);
    pthread_mutex_destroy(&data->dead);
}

int main(int argc, char **argv)
{
    t_data data;

    if (argc != 5 && argc != 6)
        return (error_print("Parameter Error\n")); // error return
    if (var_init(&data, argc, argv) == 1)
    {
        free(data.philo);
        return (error_print("Init Error\n"));
    }
    philo_init(&data);
    freeall(&data);
    return (0); // exit 미제공
}

// https://bingu.tistory.com/7
// https://raidho.tistory.com/141?category=940489
// https://reakwon.tistory.com/98
// https://bigpel66.oopy.io/library/42/inner-circle/9
// https://techdebt.tistory.com/32
// https://www.youtube.com/watch?v=YAP0Bv_aQl8