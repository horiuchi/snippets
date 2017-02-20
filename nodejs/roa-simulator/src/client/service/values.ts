///<reference path="../../../def/angular.d.ts" />

angular.module('roa-card.data', [])
	.value('Data', {
		jobs: [
			{ id: 1, name: 'ソードウォーリア', },
			{ id: 2, name: 'クレリック', },
			{ id: 3, name: 'メイジ', },
			{ id: 4, name: 'アサシン', },
			{ id: 5, name: 'ハンマースミス', },
			{ id: 6, name: 'ハンター', },
		],
		weapons: [
			{ id: 101, name: 'ツーハンドソード', job: 1,  type: 0 },
			{ id: 102, name: 'ユル ツーハンドソード', job: 1, type: 0 },
			{ id: 103, name: 'ケン ツーハンドソード', job: 1, type: 0 },
			{ id: 104, name: 'ニイド ツーハンドソード', job: 1, type: 0 },
			{ id: 105, name: 'ウィアド ツーハンドソード', job: 1, type: 0 },
			{ id: 111, name: 'エクスキューショナー', job: 1, type: 0 },
			{ id: 112, name: 'ソン エクスキューショナー', job: 1, type: 0 },
			{ id: 113, name: 'ラグ エクスキューショナー', job: 1, type: 0 },
			{ id: 114, name: 'イス エクスキューショナー', job: 1, type: 0 },
			{ id: 115, name: 'ウィアド エクスキューショナー', job: 1, type: 0 },
			{ id: 121, name: 'ミステルテイン', job: 1, type: 0 },
			{ id: 122, name: 'ウル ミステルテイン', job: 1, type: 0 },
			{ id: 123, name: 'ユル ミステルテイン', job: 1, type: 0 },
			{ id: 124, name: 'エオ ミステルテイン', job: 1, type: 0 },
			{ id: 125, name: 'ウィアド ミステルテイン', job: 1, type: 0 },
			{ id: 131, name: 'バルムンク', job: 1, type: 0 },
			{ id: 132, name: 'イング バルムンク', job: 1, type: 0 },
			{ id: 133, name: 'エオロ バルムンク', job: 1, type: 0 },
			{ id: 134, name: 'ペオズ バルムンク', job: 1, type: 0 },
			{ id: 141, name: 'レッグバイト', job: 1, type: 2 },
			{ id: 142, name: 'マン レッグバイト', job: 1, type: 2 },
			{ id: 143, name: 'シゲル レッグバイト', job: 1, type: 1 },
			{ id: 144, name: 'ペオズ レッグバイト', job: 1, type: 1 },

			{ id: 123, name: 'スコルピオンハンマー', job: 5, type: 2 },
			{ id: 124, name: 'ソン スコルピオンハンマー', job: 5, type: 1 },
			{ id: 125, name: 'ハガル スコルピオンハンマー', job: 5, type: 3 },
			{ id: 126, name: 'ベオズ スコルピオンハンマー', job: 5, type: 2 },
		],
		grades: [
			{ id: 1, name: '銅', },
			{ id: 2, name: '銀', },
			{ id: 3, name: '金', },
		],
		weapon_cost: [
			[ 0, -5, -10, -15 ],
			[ 0, -10, -15, -20 ],
			[ 0, -15, -20, -25 ],
			[ 0, -20, -25, -30 ],
			[ 0, -25, -30, -35 ],
			[ 0, -10, -15, -25 ], // 5
		],

		skills: [
			{ id: 0, name: 'マイナス効果（赤字）', title: '赤字のスキル', job: 0, cost: 5, },
			{ id: 1, name: 'HPアップ Lv1', title: 'HP +250', job: 0, cost: 5, },
			{ id: 2, name: 'HPアップ Lv2', title: 'HP +400', job: 0, cost: 10, },
			{ id: 3, name: 'HPアップ Lv3', title: 'HP +600', job: 0, cost: 15, },
			{ id: 4, name: 'HPアップ Lv4', title: 'HP +750', job: 0, cost: 15, },
			{ id: 5, name: 'HPアップ Lv5', title: 'HP +1000', job: 0, cost: 15, },
		],
	});

