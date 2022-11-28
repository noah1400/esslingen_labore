int minimum(int *numbers, int length)
{
    int min = numbers[0];
    for (int i = 0; i < length; i++)
    {
        if (numbers[i] < min)
        {
            min = numbers[i];
        }
    }
    return min;
}