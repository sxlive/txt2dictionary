开发者: sxpoint@gmail.com & ChatGPT
编程语言: Visual Studio C++

1. 程序概述
EasyTxt2Dic 是一款用于处理文本文件中英文单词的程序。它可以从指定的文本文件中读取所有英文单词，并根据出现频率对它们进行排序，支持用户设置过滤条件，最终生成一个包含过滤后单词的文件，方便导入其他软件进行词汇学习或处理。

2. 功能特点
自动读取并过滤文本中的英文单词。
根据单词出现的频率进行排序，频率相同则按字母顺序排列。
支持过滤低频单词、短单词，以及过滤出现次数过多的常用词（如冠词、助动词等）。
能够排除复合词（包含 - 和 '）的重复统计。
支持用户自定义输出的单词文件是否包含词频。
3. 使用方法
3.1 启动程序
运行程序后，程序首先会显示以下使用说明，帮助用户了解程序的基本操作：

vbnet
Copy code
EasyTxt2Dic Read Me
Developer: sxpoint@gmail.com & ChatGPT
Language: Visual Studio CPP
How to use:
1. Run the program, specify any txt file, the program will read and filter all the English words in the file, and sort according to the frequency of use.
   The more the number of uses, the more forward, the same frequency is arranged in alphabetical order.
2. The basis for the decision is from the first valid English letter to the non-valid English letter end.
3. Words that contain (-) and (') will be ignored to reduce duplication due to possessive and compound words.
4. The user can set the minimum number and minimum length of the occurrence of words, filter low-frequency words and too simple words.
5. If the word only appears in the form of capital letters, the program will be judged as a proper noun and not counted. (Seems to judge some problems, does not always work)
6. The user can set the maximum frequency of limiting the occurrence of words, and filter out high-frequency words that occur frequently (mainly articles, auxiliary verbs, etc.).
7. Finally, it will generate a TXT document, which you can import into other word software for memorization.
3.2 操作步骤
输入文件路径:
程序会提示用户输入需要处理的文本文件路径。只需输入文件的完整路径，程序即可读取其中的内容。如果文件路径无效或不存在，程序会提示重新输入。

输出文件名称:
用户需要输入输出文件的名称，程序将生成结果文件保存在与输入文件相同的目录中。

设定单词筛选条件:
用户可以设置以下筛选条件：

最小出现次数: 设定单词在文本中至少出现的次数，低于此次数的单词将被过滤。
最小单词长度: 设定单词的最小长度，长度小于设定值的单词将被过滤。
最大出现次数限制: 设定单词在文本中的最大出现次数，高于此次数的单词将被过滤，主要用于过滤掉高频单词如冠词、助动词等。用户可以选择 0 表示不限制单词最大出现次数。
是否包含词频:
用户可以选择是否在输出文件中包含每个单词的出现次数。如果选择“是”，输出文件将包含单词及其词频，如果选择“否”，则仅包含单词本身。

生成输出文件:
程序根据用户设定的条件筛选并排序单词，最后将结果保存到用户指定的文件中。

3.3 操作示例
输入文件路径:
Enter input file path (or type 'exit' to quit): C:\Users\Documents\example.txt

输出文件名称:
Enter output file name (in the same directory as input): result.txt

最小出现次数:
Enter the minimum occurrence of words to be included: 3

最小单词长度:
Enter the minimum length of words to be included: 4

最大出现次数限制:
Enter maximum word occurrence threshold (0 for no limit): 10

是否包含词频:
Do you want to include word count in output? (y/n): y

3.4 程序输出
程序生成的输出文件 result.txt 将保存到与输入文件相同的目录中.
4. 输入要求与注意事项
程序将过滤掉所有非英文单词（例如中文字符或其他符号）。
连字符（-）和撇号（'）会被视为单词的一部分，但程序会跳过这些复合词的统计。
单字母的单词（如 "a" 或 "I"）默认会被过滤。
大写字母单词（如专有名词）默认不参与统计。
5. 常见问题
文件路径无效: 如果输入文件路径不正确，程序会提示用户重新输入正确的路径。
输出文件已存在: 如果输出文件已存在，程序会提示用户文件已存在，并停止操作，以防止覆盖现有文件。
大写单词处理: 程序将单词转换为小写字母以保证一致性，但如果一个单词全为大写且只出现一次，程序将会认为它是专有名词，并不统计此类单词。
6. 版本与更新
该版本为 Visual Studio CPP 的首个版本。如果有任何问题或需要定制其他功能，欢迎联系开发者 sxpoint@gmail.com。
