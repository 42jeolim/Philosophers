#include "philo.h"

int philo_init(t_data *data)
{
    int i;

    data->t_start = timestamp();
    i = -1;
    while (++i < data->n_philo)
    {
        printf("i : %d\n", i);
        data->philo[i].id = i + 1; // id
        data->philo[i].last_eat = 0; // last eat init
        data->philo[i].right_fork = NULL; // right_fork = null
        data->philo[i].data = data; // data 넘기기
        data->philo[i].count = 0; // m_count init

        pthread_mutex_init(&(data->philo[i].left_fork), NULL); // left_fork mutex init
        if (i == data->n_philo - 1)
            data->philo[i].right_fork = &data->philo[0].left_fork;
        else
            data->philo[i].right_fork = &data->philo[i + 1].left_fork;
        if (pthread_create(&data->philo[i].thread, NULL, &philo_life, &(data->philo[i])) != 0) // 실패 시 그냥 return
            return (-1);
    }
    i = -1;
    while (++i < data->n_philo)
        if(pthread_join(data->philo[i].thread, NULL) != 0)
            return (-1);
    return (0);
}

int ft_atoi(const char *str)
{
    int i;
    int res;
    int sign;

    i = 0;
    sign = 1;
    res = 0;
    while ((str[i] >= 9 && str[i] <= 13) || (str[i] == ' '))
        i++;
    if (str[i] == '-')
    {
        sign *= -1;
        i++;
    }
    else if (str[i] == '+')
        i++;
    while (str[i] >= '0' && str[i] <= '9')
    {
        res = res * 10 + str[i] - '0';
        i++;
    }
    printf("res: %d\n", res);
    return (res * sign);
}

int ft_isdigit(int c)
{
    if (c >= '0' && c <= '9')
        return (1);
    return (0);
}

int check_num(char **str)
{
    int i;
    int j;

    i = 1;
    while (str[i])
    {
        j = 0;
        while (str[i][j])
        {
            if (!ft_isdigit(str[i][j]))
                return(1);
            j++;
        }
        i++;
    }
    return (0);
}

int var_init(t_data *data, int argc, char **argv)
{

    pthread_mutex_init(&data->message, NULL);
    pthread_mutex_init(&data->m_stop, NULL);
    pthread_mutex_init(&data->m_eat, NULL);
    pthread_mutex_init(&data->dead, NULL);
    
    if (check_num(argv))
        return (error_print("Invalid Arguments\n"));
    data->finish = 0;
    data->philo_eat = 0;
    data->n_philo = ft_atoi(argv[1]);
    printf("%s\n", argv[1]);
    data->time_to_die = ft_atoi(argv[2]);
    data->time_to_eat = ft_atoi(argv[3]);
    data->time_to_sleep = ft_atoi(argv[4]);
    if (data->n_philo < 2 || data->time_to_die < 0 || data->time_to_eat < 0 \
        || data->time_to_sleep < 0 || data->n_philo > 250)
        printf("%d %d %d %d\n", data->n_philo, data->time_to_die, data->time_to_eat, data->time_to_sleep);
        // return (1);
    if (argc == 6)
    {
        data->n_eat = ft_atoi(argv[5]);
        if (data->n_eat <= 0)
            return (1);
    }
    data->philo = (t_philo *)malloc(sizeof(t_philo) * data->n_philo);
    if (!data->philo)
        return (-1);
    return (0);
}
