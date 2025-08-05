# STL算法

## 目录
- [非修改性算法](#)
  - [find](#find)
  - [conut](#conut)
  - [二分查找](#binary-search)
- [修改性算法](#)
  - [copy](#)
  - [replace](#):将指定范围内等于给定值的元素替换为新值
  - [reverse](#):翻转序列
- [排序算法](#)
  - [sort](#)
  - [稳定排序](#stable-sort)
  - [第n大数](#nth-element)
- [数值算法](#)
  - [accumulate](#):计算指定范围内元素的累积和
  - [计算两个序列的内积](#inner-product)
- [集合算法](#)
  - [两个有序序列的差集](#set-difference)
  - [将两个有序序列合并为一个有序序列](#merge)
- [其他算法](#)
  - [去除相邻重复元素](#unique)
  - [随机打乱序列](#shuffle)

## 非修改性算法
### find
```
template <class InputIterator, class T>
InputIterator find(InputIterator first, InputIterator last, const T& value);
```
+ InputIterator：输入迭代器类型，表示要搜索的范围的起始和结束位置。
+ first：指向范围的起始位置的迭代器。
+ last：指向范围的结束位置的迭代器（不包含）。
+ value：要查找的目标值。
+ 返回值：如果找到目标值，返回指向该元素的迭代器；如果没有找到，则返回 last

__注意事项__
1. 返回值的判断
如果未找到目标值，返回值是 last,通常需要通过比较返回值是否等于 last 来判断是否找到目标

2. 自定义对象的比较
如果要在自定义对象中使用 `std::find`，需要重载 `operator==`，以便算法能够比较对象是否相等

3. 性能
是线性查找算法，时间复杂度为 O(n)，其中 n 是范围内的元素数量

4. 范围的正确性
确保 first 和 last 指向的范围是有效的，并且 first 不大于 last

### conut
```
template <class InputIterator, class T>
typename iterator_traits<InputIterator>::difference_type count(
    InputIterator first,
    InputIterator last,
    const T& value
);
```
+ InputIterator：输入迭代器类型，表示要搜索的范围的起始和结束位置。
+ first：指向范围的起始位置的迭代器。
+ last：指向范围的结束位置的迭代器（不包含）。
+ value：要统计的目标值。
+ 返回值：返回等于目标值的元素个数，类型为 `iterator_traits<InputIterator>::difference_type`

__注意事项__
1. 返回值的判断
返回值类型是 `iterator_traits<InputIterator>::difference_type`，通常是与容器相关的整数类型 `int` `size_t`

2. 自定义对象的比较
需要重载 `operator==`，以便算法能够比较对象是否相等

3. 性能
是线性查找算法，时间复杂度为 O(n)，其中 n 是范围内的元素数量

4. 范围的正确性
确保 first 和 last 指向的范围是有效的，并且 first 不大于 last

### binary-search
用于在*有序序列*中查找是否存在某个值,基于二分查找的思想,时间复杂度为 O(log n)

只返回布尔值，表示是否找到目标值,如果需要找到目标值的位置，可以结合 `std::lower_bound` 或 `std::upper_bound` 使用
```
template <class ForwardIterator, class T>
bool binary_search(ForwardIterator first, ForwardIterator last, const T& value);
```
+ ForwardIterator：正向迭代器类型，表示要搜索的范围的起始和结束位置。
+ first：指向范围的起始位置的迭代器。
+ last：指向范围的结束位置的迭代器（不包含）。
+ value：要查找的目标值。
+ 返回值：如果找到目标值，返回 true；否则返回 false。

__还支持自定义比较函数__
```
template <class ForwardIterator, class T, class Compare>
bool binary_search(ForwardIterator first, ForwardIterator last, const T& value, Compare comp);
```
+ Compare：比较函数，用于定义元素之间的大小关系。如果未提供，会使用默认的 < 比较运算符

## 修改性算法
### copy
用于将一个范围内的元素复制到另一个范围中,是一个线性算法，时间复杂度为 O(n)

```
template <class InputIterator, class OutputIterator>
OutputIterator copy(InputIterator first, InputIterator last, OutputIterator result);
```
+ InputIterator：输入迭代器类型，表示要复制的源范围的起始和结束位置。
+ first：指向源范围的起始位置的迭代器。
+ last：指向源范围的结束位置的迭代器（不包含）。
+ OutputIterator：输出迭代器类型，表示目标范围的起始位置。
+ result：指向目标范围的起始位置的迭代器。
+ 返回值：返回指向目标范围结束位置的迭代器（即 result + (last - first)）

### replace
用于在指定范围内将所有等于某个特定值的元素替换为另一个值

```
template <class ForwardIterator, class T>
void replace(ForwardIterator first, ForwardIterator last, const T& old_value, const T& new_value);
```
+ ForwardIterator：正向迭代器类型，表示要操作的范围的起始和结束位置。
+ first：指向范围的起始位置的迭代器。
+ last：指向范围的结束位置的迭代器（不包含）。
+ `old_value`：要被替换的旧值。
+ `new_value`：用于替换的新值。

如果需要更复杂的替换逻辑（例如基于条件的替换），可以结合 `std::replace_if` 使用，后者允许传入一个谓词函数来定义替换条件。

### reverse
反转指定范围内的元素顺序,要求输入范围的迭代器是双向迭代器，即支持双向遍历

```
template <class BidirectionalIterator>
void reverse(BidirectionalIterator first, BidirectionalIterator last);
```
+ BidirectionalIterator：双向迭代器类型，表示要反转的范围的起始和结束位置。
+ first：指向范围的起始位置的迭代器。
+ last：指向范围的结束位置的迭代器(不包含)

## 排序算法
### sort
指定范围内的元素进行排序,要求输入范围的迭代器是随机访问迭代器，是不稳定的排序算法,平均时间复杂度为 O(n log n)

```
template <class RandomAccessIterator>
void sort(RandomAccessIterator first, RandomAccessIterator last);
```
+ RandomAccessIterator：随机访问迭代器类型，表示要排序的范围的起始和结束位置
+ first：指向范围的起始位置的迭代器
+ last：指向范围的结束位置的迭代器（不包含）

此外，std::sort 还支持自定义比较函数
```
template <class RandomAccessIterator, class Compare>
void sort(RandomAccessIterator first, RandomAccessIterator last, Compare comp);
```

### stable-sort
是一个稳定排序算法,对指定范围内的元素进行排序，同时保证相等元素的相对顺序不变

```
template <class RandomAccessIterator>
void stable_sort(RandomAccessIterator first, RandomAccessIterator last);

template <class RandomAccessIterator, class Compare>
void stable_sort(RandomAccessIterator first, RandomAccessIterator last, Compare comp);
```
+ first 和 last：随机访问迭代器，分别指向要排序范围的起始位置和结束位置（不包含）
+ Compare：可选的比较函数，用于定义排序规则。如果未提供，默认使用 < 运算符

如果有足够的额外内存，`std::stable_sort` 的时间复杂度为 O(n log n),内存不足，时间复杂度可能退化为 O(n log² n)


### nth-element
用于部分排序序列，使得第 k 小的元素被放置到正确的位置，同时保证所有在它之前的元素都不大于它，所有在它之后的元素都不小于它,平均时间复杂度：O(n),最坏时间复杂度：O(n²)

```
template <class RandomIt>
void nth_element(RandomIt first, RandomIt nth, RandomIt last);

template <class RandomIt, class Compare>
void nth_element(RandomIt first, RandomIt nth, RandomIt last, Compare comp);
```
+ first：指向序列起始位置的随机访问迭代器。
+ nth：指向序列中第 k 个位置的迭代器（0-based index）。
+ last：指向序列结束位置的迭代器。
+ comp（可选）：自定义比较函数，默认使用 std::less

> 不会完全排序整个序列，它只保证第 k 小的元素在正确的位置上
> 该算法的性能优于完全排序

## 数值算法
### accumulate 
用于计算指定范围内元素的累积和,时间复杂度为 O(n)

`std::accumulate` 从 first 开始，逐个处理范围内的元素，将每个元素与累积结果进行操作（默认为加法），并将最终结果返回

```
template <class InputIterator, class T>
T accumulate(InputIterator first, InputIterator last, T init);

template <class InputIterator, class T, class BinaryOperation>
T accumulate(InputIterator first, InputIterator last, T init, BinaryOperation op);
```
+ InputIterator：输入迭代器类型，表示要操作的范围的起始和结束位置。
+ first：指向范围的起始位置的迭代器。
+ last：指向范围的结束位置的迭代器（不包含）。
+ T：累积结果的类型。
+ init：初始值，用于开始累积操作。
+ BinaryOperation（可选）：二元操作函数，用于定义累积操作。如果未提供，默认使用加法操作 `std::plus<T>` [预定义函数符](./containers.md#)

### inner-product

## 集合算法
### set-difference
### merge

## 其他算法
### unique
用于移除序列中相邻的重复元素,并返回一个指向“新序列”结束位置的迭代器。它不会改变原序列的长度，而是将重复元素移动到序列末尾，并返回一个指向“有效部分”结束位置的迭代器。因此，通常需要结合容器的 erase 方法来真正移除重复元素,O(n)

```
template <class ForwardIterator>
ForwardIterator unique(ForwardIterator first, ForwardIterator last);

template <class ForwardIterator, class BinaryPredicate>
ForwardIterator unique(ForwardIterator first, ForwardIterator last, BinaryPredicate pred);
```
+ ForwardIterator：正向迭代器类型，表示要操作的序列的起始和结束位置。
+ first：指向序列起始位置的迭代器。
+ last：指向序列结束位置的迭代器（不包含）。
+ BinaryPredicate（可选）：二元谓词函数，用于定义两个元素是否相等。如果未提供，默认使用 operator==

### shuffle
随机打乱指定范围内元素的顺序

```
template <class RandomAccessIterator, class URNG>
void shuffle(RandomAccessIterator first, RandomAccessIterator last, URNG&& g);
```
+ first 和 last：随机访问迭代器，分别指向要打乱范围的起始位置和结束位置（不包含）
+ URNG：均匀随机数生成器,例如 `std::mt19937` 或 `std::default_random_enginei`

```
// 使用随机数生成器
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::mt19937 rng(seed);

    // 打乱顺序
    std::shuffle(vec.begin(), vec.end(), rng);
```
