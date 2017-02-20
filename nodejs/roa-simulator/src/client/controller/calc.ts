///<reference path="../../../def/angular.d.ts" />

angular.module('roa-card.calc', [
  'roa-card.data',
])
  .controller('CalculateCtrl', function ($scope, $timeout, $log, Data) {
		$scope.data = Data;

		$scope.weapon = $scope.data.weapons[0];
		$scope.grade = $scope.data.grades[0];
		$scope.skill1 = $scope.data.skills[0];
		$scope.skill2 = null;

		$scope.calcCost = function() {
			var base = $scope.data.weapon_cost[$scope.weapon.type][$scope.grade.id];
			var skill = $scope.skill1.cost;
			if ($scope.skill2 != null) {
				skill += $scope.skill2.cost;
			}
			$scope.totalCost = skill - base;
		};
		$scope.calcCost();
	});

