// var simple_chart_config = {
//     chart: { container: "#OrganiseChart-simple" },
//     nodeStructure: {
//         text: {
//             0: "'->.S",
//             1: "A->.aA",
//             2: "A->.b",
//             3: "S->.AA",
//         },
//         children: [
//             {
//                 text: {
//                     4: "A->.aA",
//                     5: "A->.b",
//                     6: "S->A.A",
//                 },
//                 children: [
//                     {
//                         text: {
//                             7: "S->AA.",
//                         },
//                     },
//                 ]
//             },
//             {
//                 text:
//                 {
//                     8: "'->S.",
//                 },
//             },
//             {
//                 text:
//                 {
//                     9: "A->a.A",
//                     10: "A->.aA",
//                     11: "A->.b",
//                 },
//                 children: [
//                     {
//                         text:
//                         {
//                             12: "A->aA.",
//                         },
//                     },
//                     {
//                         text:
//                         {
//                             13: "SELF-LOOP"
//                         }
//                     },
//                     {
//                         text:
//                         {
//                             14: "A->b.",
//                         },
//                     },
//                 ]
//             },
//             {
//                 text: {
//                     15: "A->b.",
//                 },
//             },
//         ]
//     }
// };

var simple_chart_config = { chart: { container: "#OrganiseChart-simple" }, nodeStructure: { text: { 0: "'->.S", 1: "A->.aA", 2: "A->.b", 3: "S->.AA", }, children: [{ text: { 4: "A->.aA", 5: "A->.b", 6: "S->A.A", }, children: [{ text: { 7: "S->AA.", }, }, { text: { 8: "A->a.A", 9: "A->.aA", 10: "A->.b", }, children: [{ text: { 11: "A->aA.", }, }, { text: { 12: "SELF-LOOP" } }, { text: { 13: "A->b.", }, },] }, { text: { 14: "A->b.", }, },] }, { text: { 15: "'->S.", }, }, { text: { 16: "A->a.A", 17: "A->.aA", 18: "A->.b", }, children: [{ text: { 19: "A->aA.", }, }, { text: { 20: "SELF-LOOP" } }, { text: { 21: "A->b.", }, },] }, { text: { 22: "A->b.", }, },] } };
