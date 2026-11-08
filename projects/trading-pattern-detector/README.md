# Trading_Bot

```markdown
## File Structure

```
Trading_Bot/
├── README.md
├── LICENSE
├── .gitignore
├── src/
│   ├── enums/
│   │   ├── pattern_types.pine
│   │   └── detection_status.pine
│   ├── types/
│   │   └── pattern_info.pine
│   ├── patterns/
│   │   ├── double_top.pine
│   │   ├── bullish_flag.pine
│   │   ├── head_and_shoulders.pine
│   │   └── ... (other pattern files)
│   ├── utils/
│   │   ├── pivot_points.pine
│   │   ├── calculations.pine
│   │   └── helpers.pine
│   ├── multi_timeframe.pine
│   └── main_library.pine
├── examples/
│   ├── indicator_example.pine
│   └── strategy_example.pine
├── tests/
│   ├── test_double_top.pine
│   ├── test_bullish_flag.pine
│   └── ... (other test files)
├── docs/
│   ├── usage.md
│   ├── patterns.md
│   └── architecture.md
└── build/
    ├── build.sh
    └── build.ps1
```